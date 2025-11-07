#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

typedef struct {
    int instance_count; 
    int tank_count;
    int healer_count;
    int dps_count;
    int time_min;
    int time_max;
} CONFIG;

typedef struct {
    int player_id;
    bool available;       
    bool is_tank;
    bool is_healer;
    bool is_dps;
} PLAYER;

typedef struct {
    PLAYER *players;
    int total_count;
    int tank_count;
    int healer_count;
    int dps_count;
    pthread_mutex_t lock; 
} PLAYER_LIST;

typedef struct {
    pthread_t thread;
    int id;
    bool is_party_complete;
    int time_min;
    int time_max;
    PLAYER *party;         
    int party_size;
    //int total_party_runs;
    //int time_active;
    volatile bool *running;
    PLAYER_LIST *shared_pool; 
} INSTANCE;

typedef struct {
    pthread_t thread;
    int id;
    CONFIG config;
    INSTANCE *instances;
    volatile bool running;
    PLAYER_LIST *pool;
} MAIN_THREAD_DATA;

void *instance_thread(void *arg);
pthread_mutex_t global_log_lock = PTHREAD_MUTEX_INITIALIZER;

CONFIG set_config() {
    CONFIG config_data;

    printf("Enter maximum number of concurrent instances: ");
    if (scanf("%d", &config_data.instance_count) != 1 || config_data.instance_count <= 1) {
        printf("Invalid input. Defaulting instance_count to 1.\n");
        config_data.instance_count = 1;
        while (getchar() != '\n'); 
    }

    printf("Enter number of tanks in the queue: ");
    if (scanf("%d", &config_data.tank_count) != 1 || config_data.tank_count < 1) {
        printf("Invalid input. Defaulting tank_count to 1.\n");
        config_data.tank_count = 1;
        while (getchar() != '\n');
    }

    printf("Enter number of healers in the queue: ");
    if (scanf("%d", &config_data.healer_count) != 1 || config_data.healer_count < 1) {
        printf("Invalid input. Defaulting healer_count to 1.\n");
        config_data.healer_count = 1;
        while (getchar() != '\n');
    }

    printf("Enter number of DPS in the queue: ");
    if (scanf("%d", &config_data.dps_count) != 1 || config_data.dps_count < 3) {
        printf("Invalid input. Defaulting dps_count to 3.\n");
        config_data.dps_count = 3;
        while (getchar() != '\n');
    }

    printf("Enter minimum instance completion time (seconds): ");
    if (scanf("%d", &config_data.time_min) != 1 || config_data.time_min <= 0) {
        printf("Invalid input. Defaulting time_min to 1.\n");
        config_data.time_min = 1;
        while (getchar() != '\n');
    }

    printf("Enter maximum instance completion time (seconds): ");
    if (scanf("%d", &config_data.time_max) != 1 || config_data.time_max <= 0) {
        printf("Invalid input. Defaulting time_max to 10.\n");
        config_data.time_max = 10;
        while (getchar() != '\n');
    }

    if (config_data.time_max < config_data.time_min) {
        int tmp = config_data.time_min;
        config_data.time_min = config_data.time_max;
        config_data.time_max = tmp;
    }

    return config_data;
}

CONFIG read_config() {
    CONFIG config_data;
    FILE *fptr = fopen("config.txt", "r");
    if (!fptr) {
        perror("Error opening config.txt");
        exit(1);
    }

    if (fscanf(fptr, "%d %d %d %d %d %d",
               &config_data.instance_count,
               &config_data.tank_count,
               &config_data.healer_count,
               &config_data.dps_count,
               &config_data.time_min,
               &config_data.time_max) != 6) {
        fprintf(stderr, "Invalid config file format.\n");
        exit(1);
    }

    fclose(fptr);
    return config_data;
}

void clear_file(int instance_count) {
    char filename[64];
    FILE *fptr;

    for (int id = 0; id < instance_count; id++) { 
        snprintf(filename, sizeof(filename), "thread_outputs/instance_%d.txt", id);
        fptr = fopen(filename, "w");  
        if (fptr) fclose(fptr);
    }

    fptr = fopen("thread_outputs/player_list.txt", "w");
    if (fptr) fclose(fptr);
}

void print_player_list(const PLAYER_LIST *pool) {
    FILE *fp = fopen("thread_outputs/player_list.txt", "w");

    if (!fp) {
        perror("Failed to open player list file");
        return;
    }

    fprintf(fp, "======= PLAYER LIST =======\n\n");
    fprintf(fp, "Total players: %d\n", pool->total_count);
    fprintf(fp, "Tanks: %d | Healers: %d | DPS: %d\n\n", pool->tank_count, pool->healer_count, pool->dps_count);

    for (int i = 0; i < pool->total_count; i++) {
        const PLAYER *p = &pool->players[i];
        fprintf(fp, "Player ID: %d\tRole: ", p->player_id);

        if (p->is_tank)
            fprintf(fp, "Tank\n");
        else if (p->is_healer)
            fprintf(fp, "Healer\n");
        else if (p->is_dps)
            fprintf(fp, "DPS\n");
    }

    fclose(fp);
}

void instance_log(int instance_id, const char *format, ...) {
    FILE *fp;
    char filename[128];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[32];

    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", t);
    snprintf(filename, sizeof(filename), "thread_outputs/instance_%d.txt", instance_id);
    
    va_list args1, args2;
    va_start(args1, format);
    va_copy(args2, args1);

    // Individual instance log
    fp = fopen(filename, "a");
    if (fp) {
        fprintf(fp, "%s ", timestamp);
        vfprintf(fp, format, args1);
        fprintf(fp, "\n");
        fclose(fp);
    }

    // Main log
    pthread_mutex_lock(&global_log_lock);
    FILE *main_fp = fopen("thread_outputs/main.log", "a");
    if (main_fp) {
        fprintf(main_fp, "%s [Instance %d] ", timestamp, instance_id);
        vfprintf(main_fp, format, args2);
        fprintf(main_fp, "\n");
        fclose(main_fp);
    }
    pthread_mutex_unlock(&global_log_lock);

    va_end(args1);
    va_end(args2);
}

static unsigned int rand_r_win(unsigned int *seed) {
    *seed = *seed * 1103515245 + 12345;
    return (*seed / 65536) % 32768;
}

void *instance_thread(void *arg) {
    INSTANCE *instance = (INSTANCE *)arg;

    int time_min = instance->time_min;
    int time_max = instance->time_max;
    int tmp, range, duration;
    int total_party_runs = 0, time_active = 0;
    char party_desc[256];

    // Create a thread-local seed unique per thread
    unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)pthread_self();

    instance_log(instance->id, "Instance [%d] started", instance->id);

    while (*(instance->running)) {
        instance_log(instance->id, "Searching for party");

        Sleep(1000);

        pthread_mutex_lock(&instance->shared_pool->lock);

        int found_tank = -1, found_healer = -1, found_dps[3] = {-1, -1, -1};
        int dps_found = 0;

        for (int i = 0; i < instance->shared_pool->total_count; i++) {
            PLAYER *p = &instance->shared_pool->players[i];
            if (!p->available) continue;

            if (p->is_tank && found_tank == -1) {
                found_tank = p->player_id; p->available = false;
            } else if (p->is_healer && found_healer == -1) {
                found_healer = p->player_id; p->available = false;
            } else if (p->is_dps && dps_found < 3) {
                found_dps[dps_found++] = p->player_id;
                p->available = false;
            }

            if (found_tank != -1 && found_healer != -1 && dps_found == 3)
                break;
        }

        if (found_tank != -1 && found_healer != -1 && dps_found == 3) {
            instance->is_party_complete = true;
        } else {
            // If not enough players, wait 
            pthread_mutex_unlock(&instance->shared_pool->lock);
            Sleep(1000);
            continue;
        }

        pthread_mutex_unlock(&instance->shared_pool->lock);

        if (time_max < time_min) { tmp = time_min; time_min = time_max; time_max = tmp; }
        range = time_max - time_min + 1;
        duration = time_min + (range > 0 ? rand_r_win(&seed) % range : 0);

        snprintf(party_desc, sizeof(party_desc),
                 "Party found! Starting run for %d seconds: Party consists of %d_tank, %d_healer, %d_dps, %d_dps, %d_dps",
                 duration, found_tank, found_healer, found_dps[0], found_dps[1], found_dps[2]);
        instance_log(instance->id, "%s", party_desc);

        Sleep(duration * 1000);
        time_active += duration;

        pthread_mutex_lock(&instance->shared_pool->lock);

        // Place players back into the pool
        for (int i = 0; i < instance->shared_pool->total_count; i++) {
            PLAYER *p = &instance->shared_pool->players[i];
            if (p->player_id == found_tank || p->player_id == found_healer ||
                p->player_id == found_dps[0] || p->player_id == found_dps[1] || p->player_id == found_dps[2]) {
                p->available = true;
            }
        }
        pthread_mutex_unlock(&instance->shared_pool->lock);

        instance_log(instance->id, "Party is done, placing players back into the pool");
        total_party_runs += 1;
        instance->is_party_complete = false;
    }

    instance_log(instance->id, "Instance [%d] stopping", instance->id);
    instance_log(instance->id, "Total parties accepted into dungeon: %d", total_party_runs);
    instance_log(instance->id, "Total active time: %d", time_active);
    return NULL;
}


void *main_thread(void *arg) {
    MAIN_THREAD_DATA *mtd = (MAIN_THREAD_DATA *)arg;
    CONFIG config = mtd->config;
    INSTANCE *instances = mtd->instances;

    char user_input[32] = {0};
    int index = 0;

    for (int i = 0; i < config.instance_count; i++) {
        printf("Instance %d is initializing...\n", i);
        pthread_create(&instances[i].thread, NULL, instance_thread, &instances[i]);
    }

    printf("Type \"Exit\" to terminate the program.\n\n");

    // Keyboard polling logic
    while (mtd->running) {
        if (_kbhit()) {
            char ch = _getch();

            if (ch == '\r' || ch == '\n') {
                user_input[index] = '\0';
                printf("\n");  

                if (strcmp(user_input, "Exit") == 0 || strcmp(user_input, "exit") == 0) {
                    printf("Stopping all instances...\n");
                    mtd->running = false;
                    break;
                }

                index = 0;
                user_input[0] = '\0';
                printf("Type \"Exit\" to terminate the program.\n");
            } 
            else if (ch == '\b') { 
                if (index > 0) {
                    index--;
                    user_input[index] = '\0';
                    printf("\b \b");  
                    fflush(stdout);
                }
            } 
            else if (isprint((unsigned char)ch)) {  
                if (index < (int)sizeof(user_input) - 1) {
                    user_input[index++] = ch;
                    user_input[index] = '\0';
                    putchar(ch);  
                    fflush(stdout);
                }
            }
        }
        Sleep(50);
    }

    for (int i = 0; i < config.instance_count; i++) {
        pthread_join(instances[i].thread, NULL);
        printf("Instance %d stopped.\n", i);
    }

    printf("All instances terminated. Exiting main thread.\n");
    return NULL;
}


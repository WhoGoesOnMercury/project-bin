#include "instance.h"

int main(void) {
    srand((unsigned)time(NULL));

    MAIN_THREAD_DATA mtd = {0};

    // Choose config mode: 0 = user input, 1 = read config file
    int config_type = 0;
    if (config_type == 0) {
        mtd.config = set_config();
    } else {
        mtd.config = read_config();
    }

    clear_file(mtd.config.instance_count);

    PLAYER_LIST pool = {0};
    int total_players = mtd.config.tank_count + mtd.config.healer_count + mtd.config.dps_count;
    if (mtd.config.tank_count < 1 || mtd.config.healer_count < 1 || mtd.config.dps_count < 3) {
        printf("Insufficient players in the pool. Exiting program.");
        Sleep(3000);
        return 0;
    }
    pool.players = calloc(total_players, sizeof(PLAYER));
    pool.total_count = total_players;
    pool.tank_count = mtd.config.tank_count;
    pool.healer_count = mtd.config.healer_count;
    pool.dps_count = mtd.config.dps_count;
    pthread_mutex_init(&pool.lock, NULL);

    // Fill player roles in the pool
    int idx = 0;
    for (int i = 0; i < pool.tank_count; i++, idx++)
        pool.players[idx] = (PLAYER){ .player_id = idx, .available = true, .is_tank = true };
    for (int i = 0; i < pool.healer_count; i++, idx++)
        pool.players[idx] = (PLAYER){ .player_id = idx, .available = true, .is_healer = true };
    for (int i = 0; i < pool.dps_count; i++, idx++)
        pool.players[idx] = (PLAYER){ .player_id = idx, .available = true, .is_dps = true };

    mtd.running = true;
    mtd.pool = &pool;

    print_player_list(mtd.pool);
    mtd.instances = calloc(mtd.config.instance_count, sizeof(INSTANCE));
    if (!mtd.instances) {
        perror("calloc instances");
        return 1;
    }

    // Initialize the instances here 
    for (int i = 0; i < mtd.config.instance_count; ++i) {
        INSTANCE *inst = &mtd.instances[i];
        inst->id = i;
        inst->is_party_complete = false;
        inst->time_min = mtd.config.time_min;
        inst->time_max = mtd.config.time_max;
        inst->shared_pool = &pool;
        inst->running = &mtd.running;
    }

    // Create main thread
    if (pthread_create(&mtd.thread, NULL, main_thread, &mtd) != 0) {
        perror("pthread_create main_thread");
        free(mtd.instances);
        return 1;
    }

    pthread_join(mtd.thread, NULL);

    // Free allocated memory
    printf("Freeing allocated memory.");
    free(pool.players);
    free(mtd.instances);
    pthread_mutex_destroy(&pool.lock);
    return 0;
}

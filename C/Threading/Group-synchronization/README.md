# Thread Synchronization

This project aims to simulate thread synchronization through an RPG-like theme. 
Basically, there is a pool of players `P` and a number of instances `N`. Each
instance searches for three (3) DPS players, one (1) tank, one (1) healer to
complete a party and start the countdown for the instance completion. When players
are in an instance, they cannot be in another instance. When an instance completes,
players are returned to the pool. The main challenge is the race condition between
instances, where they try to get players. 

The config file contains the following:
1. Number of instance threads               `(N)`   
2. Number of 'tank' players                 `(T)`   
3. Number of 'healer' players               `(H)`   
4. Number of 'DPS' players                  `(D)`
5. Minimum time for instance completion     `(Tmin)`
6. Maximum time for instance completion     `(Tmax)`

Conditions:
i. `N > 0`
ii. `(T >= 1) && (H >= 1) && (D >= 3)`
iii. `Tmax > Tmin > 0`

The config file can be manually set in the program. Simply change the `int` variable
`config_type` to `0` in `main.c`.

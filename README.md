# so_long
This project is a small 2D Bomberman game using minilibx, a graffic library used at 42. It uses textures, sprites and tiles.



## Description
## Commands
* Run<br />
```
make
./so_long [map]       ex: ./so_long maps/map_large.ber
```

* QWERTY<br />
Up = W<br />
Down = S<br />
Left = A<br />
Right = D<br />

* AZERTY<br />
Up = Z<br />
Down = S<br />
Left = Q<br />
Right = D<br />
* Set bomb = B<br />
* Quit = ESC


This is a simple valid map:
```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

* The map must be closed/surrounded by walls, if not the program must returns an error.
* It must have at least one exit, one collectible, and one starting position.
* It must be rectangular.

# sync2d
## Description
```sync2d``` is a [daemon](https://en.wikipedia.org/wiki/Daemon_(computing)) synchronizing content between two directories. In other words, from the directory given as a source, files are copied or mapped to the directory given as the destination if they don't exist there. Files that exist in the destination directory but don't exist in the source directory are being removed. These actions take place every defined period of time. The method by which files are created in the destination directory depends on their size. Bigger files are mapped, smaller ones are copied. Period and limit size can be defined by the user. During the scan, everything that is not a regular file is ignored, except subdirectories that can also be scanned recursively with the appropriate option turned on. There is a possibility to shorten the period by "waking up" process with a script.
## Build
```
# Clone this repository
$ git clone https://github.com/pawelsiemieniuk/sync2d.git

# Go into the repository
$ cd sync2d

# Build
$ make build
```
Built program can be found inside [bin](bin).
## Run

```
# Run program
$ ./bin/sync2d [OPTION]... SRC DST
```
```SRC``` - Path to source directory from which files will be copied or mapped.

```DST``` - Path to destination directory to which files will be copied or mapped.
### Options
* ```-t T``` - Sets period ```T``` (in seconds) between every cycle of program. In that time daemon will be sleeping.
* ```-s S``` - Sets size ```S``` (in bytes) for files after which they will be mapped rather than copied.
* ```-R``` - Turn on scanning subdirectories. 

In default state ```T = 300```, ```S = 256```, ```R - OFF```
## Interactions
### Interrupt sleep
Program will immediately end sleeping phase and start scanning cycle. After that will go to sleep as usual.
```
# Wake up
$ ./wakeup.sh
```
### Kill process
```
# Kill process
$ ./kill
```
## Unresolved problems
* Empty subdirectories from source directory won't be copied to the destination directory.
* Empty subdirectories from destination directory won't be removed.

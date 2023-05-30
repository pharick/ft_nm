#!/bin/sh

./nm $1 > my.txt
nm $1 > system.txt
diff my.txt system.txt

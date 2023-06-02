#!/bin/sh

./nm $@ > my.txt
nm $@ > system.txt
diff my.txt system.txt

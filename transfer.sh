#! /bin/bash
#should be executed like this: sudo ./script.sh <id_of_ubuntu_container> <id_of_openio_container>

sudo docker exec -it $1 bash -c "cd /EPFL_internship/auxiliary && gcc remote.c -o remote -L/oio-sds/core  -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -lglib-2.0 -I/oio-sds/core -loiosds -loiocore"

echo 'Compiled...'


touch tmp_remote

sudo docker cp $1:/EPFL_internship/auxiliary/remote tmp_remote

docker cp tmp_remote $2:/root/.ssh/EPFL_internship/auxiliary/remote

echo 'Transfered...'

sudo rm tmp_remote

echo 'Done.'

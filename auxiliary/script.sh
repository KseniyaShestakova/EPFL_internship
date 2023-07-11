#! /bin/bash

gcc remote.c -o remote -L/oio-sds/core  -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -lglib-2.0 -I/oio-sds/core -loiosds -loiocore

echo 'Compiled...'

git add .
git commit -m "changes in remote.c and remote (auto commit)"
git push

echo 'Pushed to Git...'

echo 'Done.'


#!/bin/sh

script=$0

count=0
while [ -L "$script" ] ; do
    script=`perl -e "print readlink(\"$script\"), \"\n\""`
    count=`expr $count + 1`

    if [ $count -gt 100 ] ; then
       echo "Too many symbolic links"
       exit 1
    fi
done

tux_dir=`dirname $script`
cd $tux_dir

./pod_racer_clone

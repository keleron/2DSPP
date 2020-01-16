for filename in $(ls inputs/ | egrep '\.TXT$')
do
  timeout 10s ./a.out inputs/$filename
done;
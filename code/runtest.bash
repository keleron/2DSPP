for filename in $(ls inputs/ | egrep '\.TXT$')
do
  timeout 30s ./a.out inputs/$filename
done;
basename "$PWD"
g++ -Wall -Wconversion -fsanitize=undefined,address --std=c++17 -o program *.cpp || exit
files=$(ls *.in)
for file in $files; do
  name="${file%.*}"
  echo "$name running"
  [ -s $file ] || { echo "? skipped "; continue; }
  ./program < "$file" > "/tmp/$name.out" || { echo "!! crashed"; exit; }
  diff -y "/tmp/$name.out" "$name.ans"  || { echo "!! failed (L: output | R: answer)"; exit; }
done
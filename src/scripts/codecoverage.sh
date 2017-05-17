RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color
BOLD=$(tput bold)
NORMAL=$(tput sgr0)
suffix='.gcda'

file_percentage_accept=100

cd workspace/

gcda_files=()
cpp_files_with_gcda=()
cpp_files=()

while IFS=  read -r -d $'\0'; do
    gcda_files+=("$REPLY")
done < <(find build/ -not -iname "*test*" -iname "*.gcda" -print0)

for i in "${gcda_files[@]}"
do
   : 
   # do whatever on $i
   cpp_files_with_gcda+=(`basename $i | sed -e s/$suffix$//`)
   #echo ${cpp_files_with_gcda[0]}
done

while IFS=  read -r -d $'\0'; do
    cpp_files+=("$REPLY")
done < <(find src/ -not -iname "*test*" -iname "*.cpp" -print0)

items=${#cpp_files_with_gcda[@]}
total=${#cpp_files[@]}
percentage=$(awk "BEGIN { pc=100*${items}/${total}; i=int(pc); print (pc-i<0.5)?i:i+1 }")

echo -ne "${BOLD}List of current .cpp files (${items}/${total} - "
echo -ne "${GREEN}"
if [ ${percentage} -lt ${file_percentage_accept} ]; then
  echo -ne "${RED}"
fi
echo -e "${percentage}%${NC}):${NORMAL}"

for i in "${cpp_files[@]}"
do
   :
   echo -ne "${RED}"
   for j in "${cpp_files_with_gcda[@]}"
   do
     if [ `basename $i` = $j ]; then
       echo -ne "${GREEN}"
     fi
   done

   echo $i
done

echo ""
echo -e "${NC}${BOLD}GCov results:${NORMAL}"

gcovr -r . --exclude=".*\.h" --exclude=".*/test/.*"

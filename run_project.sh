
FILE="./configs_parser.out"
INPUT_FILE=$1



if [ -f $FILE ]; then
    echo "Executing project with parameters $1 ..." 
    echo "$FILE $INPUT_FILE" | bash
else
    echo "No excutable file found. Check if you builded project properly or run build_* script"
fi
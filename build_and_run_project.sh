

FILE="./configs_parser.out"
INPUT_FILE=$1

if [ -f $FILE ]; then
    echo "Executing project with parameters $1 ..." 
    echo "$FILE $INPUT_FILE" | bash
else
    echo "No excutable file found. Starting building project ..."
    echo "./build_project.sh" | bash
    if [ -f $FILE ]; then
        echo "Executing project with parameters $1 ..." 
        echo "$FILE $INPUT_FILE" | bash
    else
        echo "Build failed or finished incorrectly. No executable found." 
    fi
fi
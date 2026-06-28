docker compose down

if grep -qi microsoft /proc/version;then
    docker compose \
        -f docker-compose.yml \
        -f docker-compose.wsl.yml \
        up --build -d
else
    docker compose \
        -f docker-compose.yml \
        -f docker-compose.linux.yml \
        up --build -d
fi

if [[ $(echo $?) = 0 ]];then
    docker compose exec -it sdlTutorial_samples bash
else
    echo "An error occurr in docker compose"
fi

#!/bin/bash

DOCKER_IMAGE="cuy-image"
DOCKER_FILE="Dockerfile"
DOCKER_CONTAINER="cuy-container"
WORKING_DIR="/tmp/workspace"

print_help() {
  cat <<EOF
Usage: $0 [OPTIONS]

Options:
  --build-image    Build Docker image
  --run            Run interactive container
  --build          Build project inside container
  --clean          Clean project inside container
  --test           Run tests inside container
  --cmd [CMD]      Execute command inside docker container.
  -h, --help       Show this help message

Examples:
  $0 --build-image --build
  $0 --run
  $0 --test
EOF
}

build_image() {
    echo "Building Docker image..."
    export USER_ID=$(id -u) && \
    export GROUP_ID=$(id -g) && \
    docker build . -t "${DOCKER_IMAGE}" -f "${DOCKER_FILE}" --build-arg USER_ID=$USER_ID --build-arg GROUP_ID=$GROUP_ID
}

run_container() {
	docker run --rm -it --name ${DOCKER_CONTAINER} --mount src=$(pwd),target=${WORKING_DIR},type=bind ${DOCKER_IMAGE}
}

run_cmd_container() {
    local cmd="$*"
    echo Command running in container : $cmd
    docker run --rm \
        --mount src="$(pwd)",target="$WORKING_DIR",type=bind \
        -w "$WORKING_DIR" \
        "$DOCKER_IMAGE" \
        bash -c "$cmd"
}

build_project() {
    run_cmd_container "make cuy"
}

clean_project() {
    run_cmd_container "make clean"
}

run_tests() {
    echo To be done...
}

for arg in "$@"; do
    case "$arg" in
        -h|--help)
            print_help
            exit 0
            ;;
        --build-image)
            build_image
            ;;
        --run)
            run_container
            ;;
        --build)
            build_project
            ;;
        --clean)
            clean_project
            ;;
        --test)
          run_tests
          ;;
        --cmd)
            shift
            run_cmd_container "$*"
            exit 0
            ;;
        *)
            echo "Unknown option: $arg"
            print_help
            exit 1
            ;;
  esac
done


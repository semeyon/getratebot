export TOKEN=$1

docker run -ti --name getratebot --rm -e "TOKEN=$TOKEN" semeyon/getratebot
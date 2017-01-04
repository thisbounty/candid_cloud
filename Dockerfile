FROM debian:jessie

RUN apt-get update && apt-get install -y --no-install-recommends \
  && apt-get install build-essential -y \
  && apt-get install cmake g++ libcairomm-1.0-dev -y \
  && apt-get install inotify-tools -y \
  && apt-get install potrace imagemagick -y \
  && mkdir -p /data \
  && mkdir -p /input \
  && mkdir -p /output

ADD data /data

RUN cd /data/mask_wc && make && cp ./maskwc ../maskwc
RUN chmod u+x /data/entrypoint.sh /data/cc_trace

VOLUME /input
VOLUME /output


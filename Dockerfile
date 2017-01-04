FROM debian:jessie

RUN apt-get update && apt-get install -y --no-install-recommends \
  && apt-get install build-essential cmake g++ libcairomm-1.0-dev inotify-tools potrace imagemagick -y \
  && mkdir -p /data \
  && mkdir -p /input \
  && mkdir -p /output

ADD data /data

RUN cd /data/mask_wc && make && cp ./maskwc ../maskwc
RUN chmod u+x /data/entrypoint.sh /data/cc_trace

VOLUME /input
VOLUME /output


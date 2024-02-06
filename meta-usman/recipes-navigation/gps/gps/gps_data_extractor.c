#include <gps.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


struct gps_data_packet_t{
  double time;
  int quality_mode;
  double latitude;
  double longitude;
  double altitude;
  double track;
  double ground_speed;
  double climb_speed;
  int satellites_used;
  double geoidal_separation;
  int correction_status;
  double hdop;
};

/*dump gps data*/
void dump_gps_data (const struct gps_data_packet_t * gps_data_packet,
                  const int packet_number);

/*copy the source gps data to local struct for structural purposes*/
void get_gps_data (const struct gps_data_t * __gps_data, 
                 struct gps_data_packet_t * gps_data_packet );

int main(int argc, char* argv []){

  int retVal=-1;
  struct gps_data_packet_t  gps_data_packet;
  struct gps_data_t         __gps_data;

  fprintf(stdout, "GPS is starting ...\n\n");

  if ((retVal = gps_open("localhost", "2947", &__gps_data)) == -1) {
    printf("code: %d, reason: %s.\n", retVal, gps_errstr(retVal));
    return EXIT_FAILURE;
  }

  (void)gps_stream(&__gps_data, WATCH_ENABLE | WATCH_JSON, NULL);
  int packet_number=0;

  while(1) {
    if (gps_waiting(&__gps_data, 500)) {
      if (gps_read(&__gps_data, NULL, 0) == -1) {
        printf("Error: GPS data port ould not be rea.d\n");
      } else {
        if (__gps_data.set) {

          if(sizeof(__gps_data)>= sizeof(gps_data_packet)){
            (void) get_gps_data( &__gps_data, &gps_data_packet );
            packet_number++;
            (void) dump_gps_data( &gps_data_packet, packet_number );
          } else {
            printf("Error: GPS data has insufficient size.\n");
          }

        } else {
          printf("Error: GPS data is not set.\n");
        }

      } // else, if gps_read
    } // if gps waiting
  } // while

  (void)gps_stream(&__gps_data, WATCH_DISABLE, NULL);
  (void)gps_close (&__gps_data);

  return EXIT_SUCCESS;
}



/*dump gps data*/
void dump_gps_data (const struct gps_data_packet_t * gps_data_packet, const int packet_number) {

  printf("\n--- %d: GPS DATA EXTRACTED ------------------------\n", packet_number);
  printf("Time:                             \t%lf\n", gps_data_packet->time);
  printf("Quality mode:                     \t%d\n", gps_data_packet->quality_mode );
  printf("Latitude  (degree):               \t%lf\n", gps_data_packet->latitude );
  printf("Longitude (degree):               \t%lf\n", gps_data_packet->longitude );
  printf("Altitude  (meters):               \t%lf\n", gps_data_packet->altitude );
  printf("Track:                            \t%lf\n", gps_data_packet->track );
  printf("Ground speed (meters/sec):        \t%lf\n", gps_data_packet->ground_speed );
  printf("Climb speed  (meters/sec):        \t%lf\n", gps_data_packet->climb_speed );
  printf("Satellites used:                  \t%d\n", gps_data_packet->satellites_used );
  printf("Geoidal separation (meters):      \t%lf\n", gps_data_packet->geoidal_separation );
  printf("Correction status:                \t%d\n", gps_data_packet->correction_status );
  printf("Horizontal dilution of precision: \t%lf\n\n", gps_data_packet->hdop );

}



/*copy the source gps data to local struct for structural purposes*/
void get_gps_data(const struct gps_data_t * __gps_data, 
struct gps_data_packet_t * gps_data_packet ) {

  gps_data_packet->time               = (double)__gps_data->fix.time.tv_sec;
  gps_data_packet->quality_mode       = __gps_data->fix.mode;
  gps_data_packet->latitude           = __gps_data->fix.latitude;
  gps_data_packet->longitude          = __gps_data->fix.longitude;
  gps_data_packet->altitude           = __gps_data->fix.altitude;
  gps_data_packet->track              = __gps_data->fix.track;
  gps_data_packet->ground_speed       = __gps_data->fix.speed;
  gps_data_packet->climb_speed        = __gps_data->fix.climb;


  gps_data_packet->satellites_used    = __gps_data->satellites_used;
  gps_data_packet->geoidal_separation = __gps_data->fix.sep;
  gps_data_packet->correction_status  = __gps_data->fix.status;
  gps_data_packet->hdop               = __gps_data->dop.hdop;

}


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>

#include <resource.h>
#include <rw.h>

#define MAX_THREADS (65535)
#define MAX_RES_LEN (1024)
#define MAX_READ_LEN (32)
#define MAX_WRITE_LEN (32)

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  rw_main [options]\n"                                                     \
"options:\n"                                                                  \
"  -h                  Show this help message\n"                              \
"  -r [rthreads]       Number of reader threads (Default 9)\n"                       \
"  -w [wthreads]       Number of writer threads (Default 2)\n"                       \
"  -x [rthreads]       Number of reader loops (Default 5)\n"                       \
"  -y [wthreads]       Number of writer loops (Default 5)\n"                       \

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
  {"help",          no_argument,            NULL,           'h'},
  {"rthreads",      required_argument,      NULL,           'r'},
  {"wthreads",      required_argument,      NULL,           'w'},
  {"rloops",      required_argument,      NULL,           'x'},
  {"wloops",      required_argument,      NULL,           'y'},
};

/* Globals ========================================================= */
pthread_t *readers, *writers;
pthread_mutex_t counter_mtx;
pthread_cond_t read_cond, write_cond;
ssize_t resource_counter;
size_t waiting_readers;
resource shared_resource;
readerinput *r_ins;
writerinput *w_ins;

/* Helpers ========================================================= */
static const char *
random_string() {
  char *strings[] = {
    "a"
    , "b"
    , "c"
    , "d"
    , "e"
  };

  return strings[random() % (sizeof(strings) / sizeof(const char *))];
}

static void 
init_threads(size_t rthreads, size_t wthreads) {
  r_ins = (readerinput *) malloc(sizeof(readerinput) * rthreads);
  w_ins = (writerinput *) malloc(sizeof(writerinput) * wthreads);
  readers = (pthread_t *) malloc(sizeof(pthread_t) * rthreads);
  writers = (pthread_t *) malloc(sizeof(pthread_t) * wthreads);

  for (size_t i = 0; i < wthreads; i++) {
    const char *rand = random_string();
    size_t rand_sz = strlen(rand) + 1;
    w_ins[i].write_len = rand_sz;
    w_ins[i].to_write = (char *) malloc(sizeof(char) * rand_sz);
    strncpy(w_ins[i].to_write, rand, rand_sz);
    w_ins[i].sleepy_time = random() % 5;
  }

  for (size_t i = 0; i < rthreads; i++) {
    r_ins[i].read_len = MAX_READ_LEN;
    r_ins[i].sleepy_time = random() % 10;
  }

  for (size_t i = 0; i < wthreads; i++)
    pthread_create(&writers[i], NULL, (void *) &rw_write_naive, (void *) &w_ins[i]);
    
  for (size_t i = 0; i < rthreads; i++)
    pthread_create(&readers[i], NULL, (void *) &rw_read_naive, (void *) &r_ins[i]);
}

static void 
init_rpreferred_threads(size_t rthreads, size_t wthreads, size_t rloops, size_t wloops) {
  size_t total_threads = rthreads + wthreads;
  r_ins = (readerinput *) malloc(sizeof(readerinput) * rthreads);
  w_ins = (writerinput *) malloc(sizeof(writerinput) * wthreads);
  readers = (pthread_t *) malloc(sizeof(pthread_t) * rthreads);
  writers = (pthread_t *) malloc(sizeof(pthread_t) * wthreads);

  for (size_t i = 0; i < wthreads; i++) {
    const char *rand = random_string();
    size_t rand_sz = strlen(rand) + 1;
    w_ins[i].write_len = rand_sz;
    w_ins[i].to_write = (char *) malloc(sizeof(char) * rand_sz);
    strncpy(w_ins[i].to_write, rand, rand_sz);
    w_ins[i].sleepy_time = -1;
    w_ins[i].sleepy_time_max = total_threads;
    w_ins[i].loops = wloops;
    w_ins[i].print = 1;
  }

  for (size_t i = 0; i < rthreads; i++) {
    r_ins[i].read_len = MAX_RES_LEN;
    r_ins[i].sleepy_time = -1;
    r_ins[i].sleepy_time_max = total_threads;
    r_ins[i].loops = rloops;
    r_ins[i].print = 0;
  }
    
  for (size_t i = 0; i < rthreads; i++)
    pthread_create(&readers[i], NULL, (void *) &rw_rpreferred_read, (void *) &r_ins[i]);
  for (size_t i = 0; i < wthreads; i++)
    pthread_create(&writers[i], NULL, (void *) &rw_rpreferred_write, (void *) &w_ins[i]);
}

static void 
cleanup_threads(void) {
  free(readers);
  free(writers);
  readers = NULL;
  writers = NULL;
}

static void
cleanup_inputs(size_t rthreads, size_t wthreads) {
  free(r_ins);
  r_ins = NULL;

  for (size_t i = 0; i < wthreads; i++) {
    free(w_ins[i].to_write);
    w_ins[i].to_write = NULL;
  }

  free(w_ins);
  w_ins = NULL;
}

static void Usage() {
	fprintf(stderr, "%s", USAGE);
}

/* Callbacks ========================================================= */

/* Main ========================================================= */
int main(int argc, char **argv) {
/* COMMAND LINE OPTIONS ============================================= */
  int option_char = 0;
  int rthreads = 9;
  int wthreads = 2;
  size_t rloops = 5;
  size_t wloops = 5;

  setbuf(stdout, NULL); // disable caching

  // Parse and set command line arguments
  while ((option_char = getopt_long(argc, argv, "t:hn:r:p:s:w:", gLongOptions, NULL)) != -1) {
    switch (option_char) {
      case 'h': // help
        Usage();
        exit(0);
        break;                      
      default:
        Usage();
        exit(1);
      case 'r': 
        rthreads = atoi(optarg);
        break;
      case 'w': 
        wthreads = atoi(optarg);
        break;
    }
  }

/* Initialize ========================================================= */
	// Seed the random number generator
	srandom((unsigned int) time(NULL));

  counter_mtx = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
  read_cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
  write_cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
  resource_counter = -1;
  waiting_readers = 0;

  char resource[MAX_RES_LEN];
  shared_resource.buff = resource;
  shared_resource.len = MAX_RES_LEN;
  resource_init(&shared_resource);

  init_rpreferred_threads(rthreads, wthreads, rloops, wloops);

  for (size_t i = 0; i < wthreads; i++) {
    //writeroutput *output = NULL;
    //pthread_join(writers[i], (void *) &output);
    pthread_join(writers[i], NULL);
    //fprintf(stderr, "%s\n", output->output);
    //rw_free_writeroutput(output);
  }

  for (size_t i = 0; i < rthreads; i++) {
    //readeroutput *output = NULL;
    //pthread_join(readers[i], (void *) &output);
    pthread_join(readers[i], NULL);
    //fprintf(stderr, "%s\n", output->output);
    //rw_free_readeroutput(output);
  }

  //cleanup_inputs(rthreads, wthreads);
  cleanup_threads();

  return 0;
}  
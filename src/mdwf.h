#ifndef MARK_B9BA8123_0F1A_40FD_8827_42266FE32F3E
#define MARK_B9BA8123_0F1A_40FD_8827_42266FE32F3E

# ifndef QOP_MDWF_DEFAULT_PRECISION
#  define QOP_MDWF_DEFAULT_PRECISION 'D'
# endif

# include <qop-mdwf3.h>
# include <stdlib.h>
# include <qmp.h>

# define q(x) qop_mdwf_##x
# define Q(x) QOP_MDWF_##x
# if QOP_MDWF_DEFAULT_PRECISION=='D'
#  define qx(x) qop_d3_mdwf_##x
#  define QX(x) QOP_D3_MDWF_##x
#  define REAL double
# endif
# if QOP_MDWF_DEFAULT_PRECISION=='F'
#  define qx(x) qop_f3_mdwf_##x
#  define QX(x) QOP_F3_MDWF_##x
#  define REAL float
# endif

/* QCD types (qa0 assumes these definitions) */
struct SUn {
  REAL _Complex u[Q(COLORS) * Q(COLORS)];
};

struct Fermion {
  REAL _Complex u[Q(COLORS) * Q(FERMION_DIM)];
};

struct ProjectedFermion {
  REAL _Complex u[Q(COLORS) * Q(PROJECTED_FERMION_DIM)];
};

/* Internal types */
struct sublattice {
  int lo[Q(DIM)];
  int hi[Q(DIM)];
};

/* structs neighbor and up_pack are defined by qa0 */
struct neighbor;
struct up_pack;

struct eo_lattice {
  int              face_size;              /* 4-d size of the face */
  int              body_size;              /* 4-d size of the body */
  int              full_size;              /* face + body */
  int             *layout2vector;          /* 4-d layout 2 vector translation */
  struct neighbor *face_neighbor;          /* neighbor data for the face */
  struct neighbor *body_neighbor;          /* neighbor data for the body */
  int              send_up_size[Q(DIM)];   /* 4-d send size in each up-dir */
  struct up_pack  *up_pack[Q(DIM)];        /* 4-d (U,f) for up-face packing */
  int              send_down_size[Q(DIM)]; /* 4-d send size in each down-dir */
  int             *down_pack[Q(DIM)];      /* 4-d (f) for down-face packing */
  int              real_size;              /* 0, 4 or 8 */ 
  int              h_valid;                /* is .handle valid? */
  QMP_msghandle_t  handle;                 /* global send&receive handle */
  QMP_msghandle_t  th[4*Q(DIM)];           /* transitory handles */
  int              th_count;               /* number of valid th[] */
  QMP_msgmem_t     mh[4*Q(DIM)];           /* memory handles for th[] */
  int              mh_count;               /* number of valid mh[] */
  QMP_mem_t       *mem[4*Q(DIM)];          /* memory for mh[] */
  int              mem_count;              /* number of valid mem[] */
  void            *send_up_buf[Q(DIM)];    /* pf up-bufs */
  void            *send_down_buf[Q(DIM)];  /* pf down-bufs */
  void            *receive_buf[2*Q(DIM)];  /* pf receive bufs (up[], down[]) */
  int              total_send;             /* bytes to send */
  int              total_receive;          /* bytes to receive */
};

/* MDWF types */
struct QX(Fermion) {
  struct Q(State) *state;
  size_t size;
  struct Fermion *even;  
  struct Fermion *odd;
};

struct QX(HalfFermion) {
  struct Q(State) *state;
  size_t size;
  struct Fermion *even;  
};

struct QX(Gauge) {
  struct Q(State) *state;
  size_t size;
  struct SUn *data;
};

/* struct ABTable is defined by qa0 */
struct ABTable;

struct Q(Parameters) {
  struct Q(State) *state;
  size_t size;
  struct ABTable *ATable;
  struct ABTable *BTable;  /* NULL if B = 1 */
  /* XXX */
};

struct Q(State) {
  int                used;            /* gc ref counter */
  size_t             allocated;       /* currently allocated bytes */
  size_t             max_allocated;   /* maximum allocation */

  int                error_latched;   /* if 0, allow error recording */
  int                fatal_error;     /* if 0, allow reseting latch */
  const char        *error;           /* error string */

  struct eo_lattice  even;            /* even sublattice */
  struct eo_lattice  odd;             /* odd sublattice */
  int               *vector2layout;   /* 4-d to layout translation table */

  double             time_sec;        /* seconds in the last routine */
  long long          flops;           /* FLOP in the last routine */
  long long          sent;            /* bytes sent in the last routine */
  long long          received;        /* bytes received in the last routine */

  int                Ls;              /* Ls */
  int                lattice[Q(DIM)]; /* 4-d lattice size */
  struct sublattice  sublattice;      /* 4-d local sublattice */
  int                node[Q(DIM)];    /* local node address */
  int                master_p;        /* are we the master? */
};

/* Implementation functions */
int q(setup_comm)(struct Q(State) *state, int real_size);
void q(free_comm)(struct Q(State) *state);

int q(set_error)(struct Q(State) *state, int fatal, const char *error);

void *q(malloc)(struct Q(State) *state, size_t bytes);
void *q(allocate_aligned)(struct Q(State) *state,
 			  size_t *size, void **aligned_ptr,
			  size_t hdr_size, size_t bulk_size);
void *q(allocate_eo)(struct Q(State) *state,
 	             size_t *size, void **aligned_ptr,
		     size_t hdr_size, int even_count, int odd_count,
		     size_t f_size);
void q(free)(struct Q(State) *state, void *ptr, size_t bytes);
void *q(step_even)(struct Q(State) *state, void *aligned_ptr, size_t fsize);
void *q(step_odd)(struct Q(State) *state, void *aligned_ptr, size_t fsize);

/* XXX  other functions */

/* Cache size */
#define CACHE_LINE_SIZE 128
#define ALIGN(p) ((void *)((((ptrdiff_t)(p))+CACHE_LINE_SIZE-1) & \
                           ~(CACHE_LINE_SIZE-1)))

#endif /* !defined(MARK_B9BA8123_0F1A_40FD_8827_42266FE32F3E) */
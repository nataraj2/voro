#include <cstdio>
#include <cmath>
using namespace std;

#include "config.hh"
#include "pre_container.hh"

pre_container_base::pre_container_base(double ax_,double bx_,double ay_,double by_,double az_,double bz_,
	bool xperiodic_,bool yperiodic_,bool zperiodic_,int ps_) :
	ax(ax_), bx(bx_), ay(ay_), by(by_), az(az_), bz(bz_),
	xperiodic(xperiodic_), yperiodic(yperiodic_), zperiodic(zperiodic_), ps(ps_),
	index_sz(init_chunk_size), pre_id(new int*[index_sz]), end_id(pre_id),
	pre_p(new double*[index_sz]), end_p(pre_p) {
		ch_id=*end_id=new int[pre_container_chunk_size];
		l_id=end_id+index_sz;e_id=ch_id+pre_container_chunk_size;
		ch_p=*end_p=new double[ps*pre_container_chunk_size];
}

pre_container_base::~pre_container_base() {
	delete [] *end_p;
	delete [] *end_id;
	while (end_id!=pre_id) {
		end_p--;
		delete [] *end_p;
		end_id--;
		delete [] *end_id;
	}
	delete [] pre_p;
	delete [] pre_id;
}

void pre_container_base::guess_optimal(int &nx,int &ny,int &nz) {
	int ptotal((end_id-pre_id)*pre_container_chunk_size+(ch_id-*end_id));
	double dx(bx-ax),dy(by-ay),dz(bz-az);
	double ilscale(pow(ptotal/(optimal_particles*dx*dy*dz),1/3.0));
	nx=int(dx*ilscale+1);
	ny=int(dx*ilscale+1);
	nz=int(dx*ilscale+1);
}

void pre_container::put(int n,double x,double y,double z) {
	if((xperiodic||(x>=ax&&x<=bx))&&(yperiodic||(y>=ay&&y<=by))&&(zperiodic||(z>=az&&z<=bz))) {
		if(ch_id==e_id) new_chunk();
		*(ch_id++)=n;
		*(ch_p++)=x;*(ch_p++)=y;*(ch_p++)=z;
	}
}

void pre_container_poly::put(int n,double x,double y,double z,double r) {
	if((xperiodic||(x>=ax&&x<=bx))&&(yperiodic||(y>=ay&&y<=by))&&(zperiodic||(z>=az&&z<=bz))) {
		if(ch_id==e_id) new_chunk();
		*(ch_id++)=n;
		*(ch_p++)=x;*(ch_p++)=y;*(ch_p++)=z;*(ch_p++)=r;
	}
}

void pre_container::setup(container &con) {
	int **c_id(pre_id),*idp,*ide,n;
	double **c_p(pre_p),*pp,x,y,z;
	while(c_id<end_id) {
		idp=*(c_id++);ide=idp+pre_container_chunk_size;
		pp=*(c_p++);
		while(idp<ide) {
			n=*(idp++);x=*(pp++);y=*(pp++);z=*(pp++);
			con.put(n,x,y,z);
		}
	}
	idp=*c_id;
	pp=*c_p;
	while(idp<ch_id) {
		n=*(idp++);x=*(pp++);y=*(pp++);z=*(pp++);
		con.put(n,x,y,z);
	}
}

void pre_container_poly::setup(container_poly &con) {
	int **c_id(pre_id),*idp,*ide,n;
	double **c_p(pre_p),*pp,x,y,z,r;
	while(c_id<end_id) {
		idp=*(c_id++);ide=idp+pre_container_chunk_size;
		pp=*(c_p++);
		while(idp<ide) {
			n=*(idp++);x=*(pp++);y=*(pp++);z=*(pp++);r=*(pp++);
			con.put(n,x,y,z,r);
		}
	}
	idp=*c_id;
	pp=*c_p;
	while(idp<ch_id) {
		n=*(idp++);x=*(pp++);y=*(pp++);z=*(pp++);r=*(pp++);
		con.put(n,x,y,z,r);
	}
}

/** Import a list of particles from standard input. */
void pre_container::import(FILE *fp) {
	int i,j;
	double x,y,z;
	while((j=fscanf(fp,"%d %lg %lg %lg",&i,&x,&y,&z))==4) put(i,x,y,z);
	if(j!=EOF) voropp_fatal_error("File import error",VOROPP_FILE_ERROR);
}

/** Import a list of particles from standard input. */
void pre_container_poly::import(FILE *fp) {
	int i,j;
	double x,y,z,r;
	while((j=fscanf(fp,"%d %lg %lg %lg %lg",&i,&x,&y,&z,&r))==5) put(i,x,y,z,r);
	if(j!=EOF) voropp_fatal_error("File import error",VOROPP_FILE_ERROR);
}

void pre_container_base::new_chunk() {
	end_id++;end_p++;
	if(end_id==l_id) extend_chunk_index();
	ch_id=*end_id=new int[pre_container_chunk_size];
	e_id=ch_id+pre_container_chunk_size;
	ch_p=*end_p=new double[ps*pre_container_chunk_size];
}

void pre_container_base::extend_chunk_index() {
	index_sz<<=1;
	if(index_sz>max_chunk_size)
		voropp_fatal_error("Absolute memory limit on chunk index reached",VOROPP_MEMORY_ERROR);
#if VOROPP_VERBOSE >=2
	fprintf(stderr,"Pre-container chunk index scaled up to %d\n",index_sz);
#endif
	int **n_id(new int*[index_sz]),**p_id(n_id),**c_id(pre_id);
	double **n_p(new double*[index_sz]),**p_p(n_p),**c_p(pre_p);
	while(c_id<end_id) {
		*(p_id++)=*(c_id++);
		*(p_p++)=*(c_p++);
	}
	delete [] pre_id;pre_id=n_id;end_id=p_id;l_id=pre_id+index_sz;
	delete [] pre_p;pre_p=n_p;end_p=p_p;
}
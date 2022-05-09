#include "ReadSTLFile.H"

class Vert
{
	public:
		int id, flag, gid, is_matched, vid;
		double x, y, z;
		long int *pid;	
};

class GlobVert
{
	public:
		double x, y, z;
};

class FaceVert
{	public:
		int id, is_matched;
		//double x, y, z;
};

class Vertxyz
{   public:
        double x, y, z;
};

class Edge
{
	public:
		std::vector<vertex_basic> vert;
		int is_empty;
		vertex_basic v1, v2;
		int is_ignore, facetag;
		
};

class FaceEdge
{
	public:
		int v1, v2;
		std::vector<vertex_basic> tri_vert;
		bool is_clipped;
};

class GlobFace
{
	public:
		int cellid, is_body, is_bc, bc, cgns_id;
		double x, y, z;
		std::vector<int> gcon;
		double area, normx, normy, normz, xcen, ycen, zcen;
};	

class Face
{
	public:
		int id, numverts, flag, in_or_out, is_bc, bc;
		double area, normx, normy, normz, xcen, ycen, zcen;
		double surf_norm_out_x, surf_norm_out_y, surf_norm_out_z;
		std::vector<FaceVert> vert;
		Vertxyz centroid;	
		std::vector<int> gcon, lcon;
		int cell_face_pair[2];
		int is_matched, is_surface, is_body;
		std::vector<triangle> tri;
		double xmin, xmax, ymin, ymax, zmin, zmax;	
		std::vector<FaceEdge> edge;
};

class Face_basic
{
	public:
		int id, numverts, merge_id;
		std::vector<vertex_basic> vert, clip_tri_vert;
		std::vector<Edge> edge, new_edge; 
		double normx, normy, normz;
		Vertxyz centroid;	
		int is_merge, merge_index, is_matched;
		std::vector<int> nei;
		long int *pid;	
		int bc;
};

class Cell
{
	public:
        int id, numverts, numfaces, numnei, is_surface, is_bndry;
		std::vector<int> nei;
		std::vector<Vert> vert;
		std::vector<Face> face;
		std::vector<Edge> edge;
		double inx, iny, inz, xmin, xmax, ymin, ymax, zmin, zmax;
		std::vector<int> bc;
		std::vector<int> child;
};

class clip_vertex
{
	public:
		int id;
		double x, y, z;
};

class clip_face
{
	public:
		int id;
		clip_vertex vert[2];
};

class clip_surf_tri
{
	public:
		std::vector<clip_face> face;
};

class BCType
{
	public:
		int bcval;
		std::vector<Face> face;	
};


class Vect
{
	public:
		double xcomp, ycomp, zcomp;
};

class vert_list{
	public:
		int fid, vid, is_matched;
		double x, y, z;
};

class Merge
{

	public:
		std::vector<int> faceid;
};

extern std::vector<Cell> cell;
extern int total_cell_count;

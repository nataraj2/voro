#include <vector>
using namespace std;
class vertex_basic
{
        public:
		double x, y, z, angle;
		int vid, edge_index;
		bool is_end;
};

class TriEdge{
	public:
		vertex_basic v1, v2;
};

class triangle
{
	public:
		double normx, normy, normz, centx, centy, centz;
		float area;
		std::vector<vertex_basic> vert; 
		double xmin, xmax, ymin, ymax, zmin, zmax;
		int bc;
		std::vector<TriEdge> edge;
};

class vertex
{
	public:
		double x, y, z, normx, normy, normz;
		double norm2x, norm2y, norm2z;	
		int flag;
		std::vector<int> nei;
		std::vector<int> tri_id;		
};
void read_stl_file(string filename, std::vector<triangle> &surf_tri, std::vector<vertex> &surf_vert, std::vector<double> &surf_min, std::vector<double> &surf_max);	
void create_unique_vertex_list(std::vector<triangle> &surf_tri, std::vector<vertex> &surf_vert);
void create_point_cloud(string outfile);
void compute_normal(vertex v1, vertex v2, vertex v3, int elemcount);
void write_files();

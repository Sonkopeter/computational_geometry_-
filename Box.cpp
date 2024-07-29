#include "Box.h"
Box:: Box(std::vector<double> v_min,std::vector<double> v_max){
    min.resize(3);
    max.resize(3);  
    for (size_t i=0;i<3;++i){
        min[i]=v_min[i];
        max[i]=v_max[i];
    }
}
bool Box:: ray_intersection(std::vector<double> cam,std::vector<double> dir,double* result){
   double tmin;
   double tmax;
   double l_dir=sqrt(scalar_product(dir,dir));
    std::vector<double> invdir = {l_dir/dir[0],l_dir/dir[1],l_dir/dir[2]};
    if (dir[0] >= 0) {
        tmin = (min[0] - cam[0]) * invdir[0];
        tmax = (max[0] - cam[0]) * invdir[0];
    }
    else {
        tmin = (max[0] - cam[0]) * invdir[0];
        tmax = (min[0] - cam[0]) * invdir[0];
    }
       double tymin;
       double tymax;

       if (dir[1]/l_dir >= 0) {
           tymin = (min[1] - cam[1]) * invdir[1];
           tymax = (max[1] - cam[1]) * invdir[1];
       }
       else {
           tymin = (max[1] - cam[1])  * invdir[1];
           tymax = (min[1] - cam[1]) * invdir[1];
       }

       if ((tmin > tymax) || (tymin > tmax))
           return false;

       if (tymin > tmin)
           tmin = tymin;

       if (tymax < tmax)
           tmax = tymax;

       double tzmin;
       double tzmax;
       if (invdir[2] >= 0) {
           tzmin = (min[2] - cam[2]) * invdir[2];
           tzmax = (max[2] - cam[2]) * invdir[2];
       }
       else {
           tzmin = (max[2] - cam[2]) * invdir[2];
           tzmax = (min[2] - cam[2]) * invdir[2];
       }

       if ((tmin > tzmax) || (tzmin > tmax))
           return false;

       if (tzmin > tmin)
           tmin = tzmin;

       if (tzmax < tmax)
           tmax = tzmax;
       *result = tmin;
       if (*result < 0) {
           *result = tmax;
           if (*result < 0) return false;
       }
       return true;
}
double Box:: light(std::vector<double> cam, std::vector<double> dir, double dist, std::vector<double> light) {
           std::vector<double> centre = { (min[0] + max[0]) / 2,(min[1] + max[1]) / 2,(min[2] + max[2]) / 2 };
           double l_dir=sqrt(scalar_product(dir,dir));
           std::vector<double> p_min_l = {min[0],max[1],min[2]};
           std::vector<double> p_min_r = { max[0],min[1],min[2] };
           std::vector<double> p_min_dir = {max[0],max[1],min[2]};
           std::vector<double> p_max_l = { max[0],min[1],max[2] };
           std::vector<double> p_max_r = { min[0],max[1],max[2] };
           std::vector<double> p_max_dir = { min[0],min[1],max[2] };

           std::vector<double> point_minl_c = {(min[0]+p_max_r[0])/2,(min[1] + p_max_r[1]) / 2,(min[2] + p_max_r[2]) / 2 };
           std::vector<double> point_minr_c = { (min[0] + p_max_l[0]) / 2,(min[1] + p_max_l[1]) / 2,(min[2] + p_max_l[2]) / 2 };
           std::vector<double> point_mind_c = { (min[0] + p_min_dir[0]) / 2,(min[1] + p_min_dir[1]) / 2,(min[2] + p_min_dir[2]) / 2 };
           std::vector<double> point_maxl_c = { (max[0] + p_min_r[0]) / 2,(max[1] + p_min_r[1]) / 2,(max[2] + p_min_r[2]) / 2 };
           std::vector<double> point_maxr_c = { (max[0] + p_min_l[0]) / 2,(max[1] + p_min_l[1]) / 2,(max[2] + p_min_l[2]) / 2 };
           std::vector<double> point_maxd_c = { (max[0] + p_max_dir[0]) / 2,(max[1] + p_max_dir[1]) / 2,(max[2] + p_max_dir[2]) / 2 };
           // left min plane
           std::vector<double> n_minl = { point_minl_c[0] - centre[0],point_minl_c[1] - centre[1],point_minl_c[2] - centre[2] };
           std::vector<double> n_minr = { point_minr_c[0] - centre[0],point_minr_c[1] - centre[1],point_minr_c[2] - centre[2] };
           std::vector<double> n_mind = { point_mind_c[0] - centre[0],point_mind_c[1] - centre[1],point_mind_c[2] - centre[2] };
           std::vector<double> n_maxl = { point_maxl_c[0] - centre[0],point_maxl_c[1] - centre[1],point_maxl_c[2] - centre[2] };
           std::vector<double> n_maxr = { point_maxr_c[0] - centre[0],point_maxr_c[1] - centre[1],point_maxr_c[2] - centre[2] };
           std::vector<double> n_maxd = { point_maxd_c[0] - centre[0],point_maxd_c[1] - centre[1],point_maxd_c[2] - centre[2] };
           double scal_n_minl = sqrt(scalar_product(n_minl,n_minl));
           double scal_n_minr = sqrt(scalar_product(n_minr, n_minr));
           double scal_n_mind = sqrt(scalar_product(n_mind, n_mind));
           double scal_n_maxl = sqrt(scalar_product(n_maxl, n_maxl));
           double scal_n_maxr = sqrt(scalar_product(n_maxr, n_maxr));
           double scal_n_maxd = sqrt(scalar_product(n_maxd, n_maxd));
           n_minl = {n_minl[0]  / scal_n_minl,n_minl[1]/ scal_n_minl,n_minl[2]/scal_n_minl };
           n_minr = { n_minr[0] / scal_n_minr,n_minr[1] / scal_n_minr,n_minr[2] / scal_n_minr };
           n_mind = { n_mind[0] / scal_n_mind,n_mind[1] / scal_n_mind,n_mind[2] / scal_n_mind };
           n_maxl = { n_maxl[0] / scal_n_maxl,n_maxl[1] / scal_n_maxl,n_maxl[2] / scal_n_maxl };
           n_maxr = { n_maxr[0] / scal_n_maxr,n_maxr[1] / scal_n_maxr,n_maxr[2] / scal_n_maxr };
           n_maxd = { n_maxd[0] / scal_n_maxd,n_maxd[1] / scal_n_maxd,n_maxd[2] / scal_n_maxd };

            double result=0.0;
           std::vector<double> point = { cam[0] + dist * dir[0]/l_dir,cam[1] + dist * dir[1]/l_dir,cam[2] + dist * dir[2]/l_dir };
           std::vector<double> diff = { point[0] - centre[0],point[1] - centre[1],point[2] - centre[2] };
           std::vector<double> d_min_max = { std::abs(min[0] - max[0]) / 2,std::abs(min[1] - max[1]) / 2,std::abs(min[2] - max[2]) / 2 };
             double e = 1.000001;
           std::vector<int> n0 = { static_cast<int>(diff[0] / (d_min_max[0])*e),static_cast<int>(diff[1] / (d_min_max[1])*e),static_cast<int>(diff[2] /(d_min_max[2])*e) };
          std::vector<double> n = { static_cast<double>(n0[0]) ,  static_cast<double>(n0[1]),  static_cast<double>(n0[2]) };
           double scal_n = scalar_product(n,n);
          // diff = {diff[0]/sqrt(scalar_product(diff,diff)),diff[1] /sqrt(scalar_product(diff,diff)),diff[2] / sqrt(scalar_product(diff,diff)) };
          n = {n[0]/sqrt(scal_n),n[1]/sqrt(scal_n),n[2]/sqrt(scal_n)};
          light = { light[0] - point[0],light[1] - point[1],light[2] - point[2] };
          light = { light[0] / sqrt(scalar_product(light,light)),light[1] / sqrt(scalar_product(light,light)),light[2] / sqrt(scalar_product(light,light)) };
          
          std::vector<double> reflected(3);//={dir[0]-2.0*scalar_product(normal,dir)*normal[0],dir[1]-2.0*scalar_product(normal,dir)*normal[1],dir[2]-2.0*scalar_product(normal,dir)*normal[2]};
          std::vector<double> intersect(3);
          intersect = { cam[0] + dist * dir[0]/l_dir,cam[1] + dist * dir[1]/l_dir,cam[2] + dist * dir[2]/l_dir};
           double plane_minl=n_minl[0] * (point[0] - point_minl_c[0]) + n_minl[1] * (point[1] - point_minl_c[1]) + n_minl[2] * (point[2] - point_minl_c[2]);

           double plane_minr=n_minr[0] * (point[0] - point_minr_c[0]) + n_minr[1] * (point[1] - point_minr_c[1]) + n_minr[2] * (point[2] - point_minr_c[2]);

          double plane_mind=n_mind[0] * (point[0] - point_mind_c[0]) + n_mind[1] * (point[1] - point_mind_c[1]) + n_mind[2] * (point[2] - point_mind_c[2]);

          double plane_maxl=n_maxl[0] * (point[0] - point_maxl_c[0]) + n_maxl[1] * (point[1] - point_maxl_c[1]) + n_maxl[2] * (point[2] - point_maxl_c[2]);

          double plane_maxr=n_maxr[0] * (point[0] - point_maxr_c[0]) + n_maxr[1] * (point[1] - point_maxr_c[1]) + n_maxr[2] * (point[2] - point_maxr_c[2]);

          double plane_maxd=n_maxd[0] * (point[0] - point_maxd_c[0]) + n_maxd[1] * (point[1] - point_maxd_c[1]) + n_maxd[2] * (point[2] - point_maxd_c[2]);

        if (std::fabs(plane_minl)<std::numeric_limits<double>::epsilon()+0.000001f) {
        light = { light[0] - point[0],light[1] - point[1],light[2] - point[2] };
        light = { light[0] / sqrt(scalar_product(light,light)),light[1] / sqrt(scalar_product(light,light)),light[2] / sqrt(scalar_product(light,light)) };
        result = std::max(0.0, scalar_product(light, n_minl));

        //   std::cout<<n_minl[0]<<" "<<n_minl[1]<<" "<<n_minl[2];
        return result;
        }
        else
        if (std::fabs(plane_minr)<std::numeric_limits<double>::epsilon()+0.000001f) {
            light = { light[0] - point[0],light[1] - point[1],light[2] - point[2] };
            light = { light[0] / sqrt(scalar_product(light,light)),light[1] / sqrt(scalar_product(light,light)),light[2] / sqrt(scalar_product(light,light)) };
            result = std::max(0.0, scalar_product(light, n_minr));

        //   std::cout<<n_minl[0]<<" "<<n_minl[1]<<" "<<n_minl[2];
            return result;
        }
        else
            if (std::fabs(plane_mind)<std::numeric_limits<double>::epsilon()+0.000001f) {
                light = { light[0] - point[0],light[1] - point[1],light[2] - point[2] };
                light = { light[0] / sqrt(scalar_product(light,light)),light[1] / sqrt(scalar_product(light,light)),light[2] / sqrt(scalar_product(light,light)) };
                result = std::max(0.0, scalar_product(light, n_mind));

            //   std::cout<<n_minl[0]<<" "<<n_minl[1]<<" "<<n_minl[2];
                return result;
            }
            else
                if(std::fabs(plane_maxl)< std::numeric_limits<double>::epsilon()+0.000001f) {
                light = { light[0] - point[0],light[1] - point[1],light[2] - point[2] };
                light = { light[0] / sqrt(scalar_product(light,light)),light[1] / sqrt(scalar_product(light,light)),light[2] / sqrt(scalar_product(light,light)) };
                result = std::max(0.0, scalar_product(light, n_maxl));

            //   std::cout<<n_minl[0]<<" "<<n_minl[1]<<" "<<n_minl[2];
                 return result;
            }else
                    if (std::fabs(plane_maxr)< std::numeric_limits<double>::epsilon()+0.000001f) {
                        light = { light[0] - point[0],light[1] - point[1],light[2] - point[2] };
                        light = { light[0] / sqrt(scalar_product(light,light)),light[1] / sqrt(scalar_product(light,light)),light[2] / sqrt(scalar_product(light,light)) };
                        result =  std::max(0.0, scalar_product(light, n_maxr));
                    return result;
                    }
                    else
                        if (std::fabs(plane_maxd)< std::numeric_limits<double>::epsilon()+0.000001f) {
                            light = { light[0] - point[0],light[1] - point[1],light[2] - point[2] };
                            light = { light[0] / sqrt(scalar_product(light,light)),light[1] / sqrt(scalar_product(light,light)),light[2] / sqrt(scalar_product(light,light)) };
                            result = std::max(0.0, scalar_product(light, n_maxd));
                        //   std::cout<<n_minl[0]<<" "<<n_minl[1]<<" "<<n_minl[2];
                            return result;
                        }

            return result;


}
double Box:: distance(std::vector<double> cam){
   std::vector<double> center = {(max[0]+min[0])/2,(max[1]+min[1])/2,(max[2]+min[2])/2};
   double result = sqrt( (center[0]-cam[0])*(center[0]-cam[0])+(center[1]-cam[1])*(center[1]-cam[1])+(center[2]-cam[2])*(center[2]-cam[2]) );
   return result;
}

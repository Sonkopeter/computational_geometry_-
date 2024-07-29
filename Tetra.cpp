#include "Tetra.h"
Tetrahedron::Tetrahedron(std::vector<double> AA,std::vector<double> BB, std::vector<double> CC, std::vector<double> DD){
    A.resize(3);
    B.resize(3);
    C.resize(3);
    D.resize(3);
    for (size_t i=0;i<3;++i){
        A[i]=AA[i];
        B[i]=BB[i];
        C[i]=CC[i];
        D[i]=DD[i];
    }
}
bool Tetrahedron:: ray_intersection(std::vector<double> cam,std::vector<double> dir,double* t){
    std::vector<double> e1={B[0]-A[0],B[1]-A[1],B[2]-A[2]};
    std::vector<double> e2={C[0]-A[0],C[1]-A[1],C[2]-A[2]};
    std::vector<double> e3={D[0]-A[0],D[1]-A[1],D[2]-A[2]};
    std::vector<double> e4={e1[0]-e2[0],e1[1]-e2[1],e1[2]-e2[2]};
    std::vector<double> e5={e2[0]-e3[0],e2[1]-e3[1],e2[2]-e3[2]};
    std::vector<double> n1(3);
    std::vector<double> n2(3);
    std::vector<double> n3(3);
    std::vector<double> n4(3);
    vector_product(&n1,e1,e2);
    vector_product(&n2,e2,e3);
    vector_product(&n3,e1,e3);
    vector_product(&n4,e4,e5);
    n1 = {n1[0]/sqrt(scalar_product(n1,n1)),n1[1]/sqrt(scalar_product(n1,n1)),n1[2]/sqrt(scalar_product(n1,n1))};
    n2 = {n2[0]/sqrt(scalar_product(n2,n2)),n2[1]/sqrt(scalar_product(n2,n2)),n2[2]/sqrt(scalar_product(n2,n2))};
    n3={n3[0]/sqrt(scalar_product(n3,n3)),n3[1]/sqrt(scalar_product(n3,n3)),n3[2]/sqrt(scalar_product(n3,n3))};
    n4={n4[0]/sqrt(scalar_product(n4,n4)),n4[1]/sqrt(scalar_product(n4,n4)),n4[2]/sqrt(scalar_product(n4,n4))};

    double t1 = ray_intersection_triangular(cam,dir,A,B,C);
    double t2 = ray_intersection_triangular(cam,dir,A,B,D);
    double t3 = ray_intersection_triangular(cam,dir,A,C,D);
    double t4 = ray_intersection_triangular(cam,dir,B,C,D);
    //std::cout<< t1<<" "<<t2<<"  "<<t3<<"  "<<t4;
  if (std::max(t1,std::max(t2,std::max(t3,t4)))<=0){

        return false;
    }
  double maximum=std::numeric_limits<double>::max();
  *t=std::numeric_limits<double>::max();
    //std::cout<<t1;
  bool flag=false;
  if (t1>0 || t1<0) {
      flag=true;
    *t=t1;
  //    return true;
  }
  if (t2>0 || t2<0) {
      flag=true;
    *t=std::min(*t,t2);
  }
  if (t3>0 || t3<0) {
      flag=true;
    *t=std::min(*t,t3);
  }
  if (t4>0 || t4<0) {

      flag=true;
    *t=std::min(*t,t4);
  }
  if (std::fabs(*t-maximum)<std::numeric_limits<double>::epsilon()){
      *t=0;
  }

 return flag;
}
double Tetrahedron::ray_intersection_triangular(std::vector<double> cam,std::vector<double> dir,std::vector<double> v0,std::vector<double> v1,std::vector<double> v2){
    std::vector<double> e1={v1[0]-v0[0],v1[1]-v0[1],v1[2]-v0[2]};
    std::vector<double> e2={v2[0]-v0[0],v2[1]-v0[1],v2[2]-v0[2]};
    std::vector<double> n(3);
    double l_dir=sqrt(scalar_product(dir,dir));
    vector_product(&n,dir,e2);
    double scal=scalar_product(e1,n)/l_dir;
    if (fabs(scal)<std::numeric_limits<double>::epsilon()+0.000001f){
        return 0;
    }
    double reverse_scal=1/scal;
    std::vector<double> tt ={cam[0]-v0[0],cam[1]-v0[1],cam[2]-v0[2]};
    double param = scalar_product(tt,n)*reverse_scal/l_dir;
    if ((param<0) || (param >1) )
        return 0;

    std::vector<double> vec(3);
    vector_product(&vec,tt,e1);
    double param2 = scalar_product(dir,vec)*reverse_scal/l_dir;
    if ((param2<0) || (param2+param>1))
        return 0;
    return  scalar_product(e2,vec)*reverse_scal;;
}
double Tetrahedron::light(std::vector<double> cam,std::vector<double> dir,double t,std::vector<double>light){
    std::vector<double> e1={B[0]-A[0],B[1]-A[1],B[2]-A[2]};
    std::vector<double> e2={C[0]-A[0],C[1]-A[1],C[2]-A[2]};
    std::vector<double> e3={D[0]-A[0],D[1]-A[1],D[2]-A[2]};
    std::vector<double> e4={e1[0]-e2[0],e1[1]-e2[1],e1[2]-e2[2]};
    std::vector<double> e5={e1[0]-e3[0],e1[1]-e3[1],e1[2]-e3[2]};
    std::vector<double> n1(3);
    std::vector<double> n2(3);
    std::vector<double> n3(3);
    std::vector<double> n4(3);
    vector_product(&n1,e1,e2);
    vector_product(&n2,e2,e3);
    vector_product(&n3,e3,e1);
    vector_product(&n4,e5,e4);
    double l_dir=sqrt(scalar_product(dir,dir));
    n1 = {n1[0]/sqrt(scalar_product(n1,n1)),n1[1]/sqrt(scalar_product(n1,n1)),n1[2]/sqrt(scalar_product(n1,n1))};
    n2 = {n2[0]/sqrt(scalar_product(n2,n2)),n2[1]/sqrt(scalar_product(n2,n2)),n2[2]/sqrt(scalar_product(n2,n2))};
    n3 = {n3[0]/sqrt(scalar_product(n3,n3)),n3[1]/sqrt(scalar_product(n3,n3)),n3[2]/sqrt(scalar_product(n3,n3))};
    n4 = {n4[0]/sqrt(scalar_product(n4,n4)),n4[1]/sqrt(scalar_product(n4,n4)),n4[2]/sqrt(scalar_product(n4,n4))};
     std::vector<double> point={cam[0]+t*dir[0]/l_dir,cam[1]+t*dir[1]/l_dir,cam[2]+t*dir[2]/l_dir};
    std::vector<double> centre_mass={(A[0]+B[0]+C[0]+D[0])/4,(A[1]+B[1]+C[1]+D[1])/4,(A[2]+B[2]+C[2]+D[2])/4};
    std::vector<double> diff={point[0]-centre_mass[0],point[1]-centre_mass[1],point[2]-centre_mass[2]};
    double signum=scalar_product(n1,diff);
    if (signum<0){
    n1={-n1[0],-n1[1],-n1[2]};
    }
    double signum2=scalar_product(n2,diff);
    if (signum2<0){
        n2={-n2[0],-n2[1],-n2[2]};
    }
    double signum3=scalar_product(n3,diff);
    if (signum3<0){
    n3 = {-n3[0],-n3[1],-n3[2]};
    }
    double signum4=scalar_product(n4,diff);
    if (signum4<0){
    n4={-n4[0],-n4[1],-n4[2]};
    }
    double plane1 = n1[0]*(point[0]-A[0])+n1[1]*(point[1]-A[1])+n1[2]*(point[2]-A[2]);
    double plane2 = n2[0]*(point[0]-C[0])+n2[1]*(point[1]-C[1])+n2[2]*(point[2]-C[2]);
    double plane3 = n3[0]*(point[0]-A[0])+n3[1]*(point[1]-A[1])+n3[2]*(point[2]-A[2]);
    double plane4 = n4[0]*(point[0]-B[0])+n4[1]*(point[1]-B[1])+n4[2]*(point[2]-B[2]);
    double result=0.0;
    std::vector<double> reflected(3);
    std::vector<double> intersect(3);
    intersect = { cam[0] + t * dir[0]/l_dir,cam[1] + t * dir[1]/l_dir,cam[2] + t * dir[2]/l_dir};
    if (std::fabs(plane1) < std::numeric_limits<double>::epsilon()+0.000001f) {
        light = { light[0] - point[0],light[1] - point[1],light[2] - point[2] };
        light = { light[0] / sqrt(scalar_product(light,light)),light[1] / sqrt(scalar_product(light,light)),light[2] / sqrt(scalar_product(light,light)) };
        result = std::max(0.0, scalar_product(light, n1));
        reflected = { -light[0] + 2 * scalar_product(n1,light) * n1[0],-light[1] + 2 * scalar_product(n1,light) * n1[1],-light[2] + 2 * scalar_product(n1,light) * n1[2] };
        reflected = { reflected[0] / sqrt(scalar_product(reflected,reflected)),reflected[1] / sqrt(scalar_product(reflected,reflected)),reflected[2] / sqrt(scalar_product(reflected,reflected)) };
        intersect = { intersect[0] / sqrt(scalar_product(intersect,intersect)),intersect[1] / sqrt(scalar_product(intersect,intersect)),intersect[2] / sqrt(scalar_product(intersect,intersect)) };
        double specular = -scalar_product(reflected, intersect);
        specular=0.3*pow(std::max(0.0,specular),20);
       return result+specular;
    }
    else if (std::fabs(plane2) < std::numeric_limits<double>::epsilon()+0.000001f) {

        light = { light[0] - point[0],light[1] - point[1],light[2] - point[2] };
        light = { light[0] / sqrt(scalar_product(light,light)),light[1] / sqrt(scalar_product(light,light)),light[2] / sqrt(scalar_product(light,light)) };
        result = std::max(0.0, scalar_product(light, n2));
        reflected = { -light[0] + 2 * scalar_product(n2,light) * n2[0],-light[1] + 2 * scalar_product(n2,light) * n2[1],-light[2] + 2 * scalar_product(n2,light) * n2[2] };
        reflected = { reflected[0] / sqrt(scalar_product(reflected,reflected)),reflected[1] / sqrt(scalar_product(reflected,reflected)),reflected[2] / sqrt(scalar_product(reflected,reflected)) };
        intersect = { intersect[0] / sqrt(scalar_product(intersect,intersect)),intersect[1] / sqrt(scalar_product(intersect,intersect)),intersect[2] / sqrt(scalar_product(intersect,intersect)) };
        double specular = -scalar_product(reflected, intersect);
        specular=0.3*pow(std::max(0.0,specular),40);
        return result+specular;
    }
   else if (std::fabs(plane3) < std::numeric_limits<double>::epsilon()+0.000001f) {

        light = { light[0] - point[0],light[1] - point[1],light[2] - point[2] };
        light = { light[0] / sqrt(scalar_product(light,light)),light[1] / sqrt(scalar_product(light,light)),light[2] / sqrt(scalar_product(light,light)) };
        result = std::max(0.0, scalar_product(light, n3));
        reflected = { -light[0] + 2 * scalar_product(n3,light) * n3[0],-light[1] + 2 * scalar_product(n3,light) * n3[1],-light[2] + 2 * scalar_product(n3,light) * n3[2] };
        reflected = { reflected[0] / sqrt(scalar_product(reflected,reflected)),reflected[1] / sqrt(scalar_product(reflected,reflected)),reflected[2] / sqrt(scalar_product(reflected,reflected)) };
        intersect = { intersect[0] / sqrt(scalar_product(intersect,intersect)),intersect[1] / sqrt(scalar_product(intersect,intersect)),intersect[2] / sqrt(scalar_product(intersect,intersect)) };
        double specular = -scalar_product(reflected, intersect);
        specular=0.3*pow(std::max(0.0,specular),40);
        return result+specular;
    }
    else if (std::fabs(plane4)< std::numeric_limits<double>::epsilon()+0.000001f){
        light = { light[0] - point[0],light[1] - point[1],light[2] - point[2] };
        light = { light[0] / sqrt(scalar_product(light,light)),light[1] / sqrt(scalar_product(light,light)),light[2] / sqrt(scalar_product(light,light)) };
        result = std::max(0.0, scalar_product(light, n4));
        reflected = { -light[0] + 2 * scalar_product(n4,light) * n4[0],-light[1] + 2 * scalar_product(n4,light) * n4[1],-light[2] + 2 * scalar_product(n4,light) * n4[2] };
        reflected = { reflected[0] / sqrt(scalar_product(reflected,reflected)),reflected[1] / sqrt(scalar_product(reflected,reflected)),reflected[2] / sqrt(scalar_product(reflected,reflected)) };
        intersect = { intersect[0] / sqrt(scalar_product(intersect,intersect)),intersect[1] / sqrt(scalar_product(intersect,intersect)),intersect[2] / sqrt(scalar_product(intersect,intersect)) };
        double specular = -scalar_product(reflected, intersect);
        specular=0.3*pow(std::max(0.0,specular),40);
        return result+specular;
    }
    return result;
}
double Tetrahedron::distance(std::vector<double> cam){
   std::vector<double> center = {(A[0]+B[0]+C[0]+D[0])/4,(A[1]+B[1]+C[1]+D[1])/4,(A[2]+B[2]+C[2]+D[2])/4};
   double result = sqrt( (center[0]-cam[0])*(center[0]-cam[0])+(center[1]-cam[1])*(center[1]-cam[1])+(center[2]-cam[2])*(center[2]-cam[2]) );
   return result;
}

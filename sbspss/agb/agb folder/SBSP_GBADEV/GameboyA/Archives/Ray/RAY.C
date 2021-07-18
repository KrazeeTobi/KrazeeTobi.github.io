//Here's a simple and buggy raytracer...

#define maxcolor 31
#define objects 4
#define max_st 4

static int st;
int x,y;


#define mini 0.1
#define maxi 99999

#define xres 240
#define yres 160

#define taov 0.2

struct color
{
 float r,g,b;
};

struct object
{
 struct color col;
 float wo,x,y,z,a,b,c,d;
 float r,r2;
 int type;
};


 struct object s0,s1,s2,s3;
 struct light sws;
 struct object *list[objects];

struct vector
{
 float x,y,z;
};

struct vector normalize(struct vector w)
{
 float length;
 length=w.x*w.x+w.y*w.y+w.z*w.z;
 length=sqrt(length);
 if(!length)
  return w;
 w.x/=length;
 w.y/=length;
 w.z/=length;
 return w;
}

struct light
{
  float x,y,z;
  struct color col;
};

struct ray
{
 float xloc,yloc,zloc,xdir,ydir,zdir,t,x,y,z;
 int nr;
};

struct ray normalize_p(struct ray p)
{
 float length;
 length=p.xdir*p.xdir+p.ydir*p.ydir+p.zdir*p.zdir;
 length=sqrt(length);
 if(!length)
  return p;
 p.xdir/=length;
 p.ydir/=length;
 p.zdir/=length;
 return p;
}


void plane_intersection2(struct ray*,struct color*,int);
float plane_intersection(struct ray*,int);
float sphere_intersection(struct ray*,int);
void sphere_intersection2(struct ray*,struct color*,int);
int find(struct ray*,int,struct color*);

int find(struct ray* pr,int numer,struct color* r)
{
  int nr;
  float distance;
  float work;
  int i;
  nr=-1;
  distance=maxi;


  for(i=0;i<objects;i++)
   {
   if(i!=numer)
    {
    if(list[i]->type)
     work=plane_intersection(pr,i);
    else
     work=sphere_intersection(pr,i);
    if((work>0)&&(work<distance))
     {
      distance=work;
      nr=i;
     }
  }

    }
  if(nr<0)
  return(-1);

     pr->t=distance;
     pr->x=pr->xloc+pr->t*pr->xdir;
     pr->y=pr->yloc+pr->t*pr->ydir;
     pr->z=pr->zloc+pr->t*pr->zdir;
     pr->nr=nr;

    if(list[nr]->type)
      plane_intersection2(pr,r,nr);
    else
      sphere_intersection2(pr,r,nr);

  return 1;
}




 float plane_intersection(struct ray* ray,int q)
 {
  float tyu,tyu1;
  tyu=((-list[q]->d-list[q]->a*ray->xloc-list[q]->b*ray->yloc-list[q]->c*ray->zloc));
  tyu1=(list[q]->a*ray->xdir+list[q]->b*ray->ydir+list[q]->c*ray->zdir);
  if(!tyu1)
   return -1;
  tyu/=tyu1;
  return tyu;
 }

void plane_intersection2(struct ray* ray,struct color* r,int q)
 {
  float dotproduct,p1;
  struct color tcol,r1;
  struct vector tl;
  struct ray tolight,refl;
  int trg;

  tcol.r=0;
  tcol.g=0;
  tcol.b=0;
  r1.r=0;
  r1.g=0;
  r1.b=0;

  tl.x=sws.x-ray->x;
  tl.y=sws.y-ray->y;
  tl.z=sws.z-ray->z;
  tl=normalize(tl);
  tolight.xdir=tl.x;
  tolight.ydir=tl.y;
  tolight.zdir=tl.z;
  tolight.xloc=ray->x;
  tolight.yloc=ray->y;
  tolight.zloc=ray->z;
  dotproduct=(list[q]->a*tl.x+list[q]->b*tl.y+list[q]->c*tl.z);
  if((dotproduct>0)&&(find(&tolight,ray->nr,&r1))==-1)
  {
   tcol.r=dotproduct*sws.col.r;
   tcol.g=dotproduct*sws.col.g;
   tcol.b=dotproduct*sws.col.b;
  }
  if(list[q]->wo)
  {
   p1=-2*(list[q]->a*ray->xdir+list[q]->b*ray->ydir+list[q]->c*ray->zdir);
   refl.xdir=list[q]->a*p1+ray->xdir;
   refl.ydir=list[q]->b*p1+ray->ydir;
   refl.zdir=list[q]->c*p1+ray->zdir;
   refl=normalize_p(refl);
   refl.xloc=ray->x;
   refl.yloc=ray->y;
   refl.zloc=ray->z;
   if(--st<0)
     st=0;
   else
    if(find(&refl,ray->nr,&r1))
     {
      tcol.r+=list[q]->wo*r1.r;
      tcol.g+=list[q]->wo*r1.g;
      tcol.b+=list[q]->wo*r1.b;
    }
  }
 if(list[q]->b>=0)
 {
  if(!(((long int)(ray->x/14))&1))
    trg=1;
  else
    trg=0;
  if(((long int)(ray->y/14))&2)
   trg^=1;
  if(ray->x>0)
   trg^=1;
  }
  tcol.r*=list[q]->col.r*trg/3+.5;
  tcol.g*=list[q]->col.g*trg/3+.3;
  tcol.b*=list[q]->col.b*trg/3+.3;
  *r=tcol;
}

float sphere_intersection(struct ray* ray,int q)
 {
  float diffx,diffy,diffz,b,c,delta,x1,x2;

  diffx=list[q]->x-ray->xloc;
  diffy=list[q]->y-ray->yloc;
  diffz=list[q]->z-ray->zloc;
  b=-2*(diffx*ray->xdir+diffy*ray->ydir+diffz*ray->zdir);
  c=diffx*diffx+diffy*diffy+diffz*diffz-list[q]->r2;
  delta=b*b-4*c;
  if(delta<=0)
   return -1;
  delta=sqrt(delta);
  x1=(-b-delta);
  x2=(-b+delta);
  if(x1<mini||x1>maxi)
   x1=-1;
  if(x2<mini||x2>maxi)
   x2=-1;
  if(x1<0)
   {
    if(x2<0)
     return -1;
    return x2/2;
   }
  if(x2<0)
   return x1/2;
  return (x1<x2)?x1/2:x2/2;
 }


void sphere_intersection2(struct ray* ray,struct color* rs,int q)
{
 float dotproduct;
 float p1,w2;
 struct color tcol,r1;
 struct vector tl,norm,help,spot;
 struct ray tolight,refl;

 tcol.r=0;
 tcol.g=0;
 tcol.b=0;
 r1.r=0;
 r1.g=0;
 r1.b=0;

 tl.x=sws.x-ray->x;
 tl.y=sws.y-ray->y;
 tl.z=sws.z-ray->z;
 tl=normalize(tl);
 tolight.xdir=tl.x;
 tolight.ydir=tl.y;
 tolight.zdir=tl.z;
 tolight.xloc=ray->x;
 tolight.yloc=ray->y;
 tolight.zloc=ray->z;
 norm.x=(ray->x-list[q]->x)/list[q]->r;
 norm.y=(ray->y-list[q]->y)/list[q]->r;
 norm.z=(ray->z-list[q]->z)/list[q]->r;
 dotproduct=(norm.x*tl.x+norm.y*tl.y+norm.z*tl.z);
 if((dotproduct>0)&&(find(&tolight,ray->nr,&r1))==-1)
  {
   tcol.r=dotproduct*sws.col.r;
   tcol.g=dotproduct*sws.col.g;
   tcol.b=dotproduct*sws.col.b;
   tcol.r*=list[q]->col.r;
   tcol.g*=list[q]->col.g;
   tcol.b*=list[q]->col.b;
   if(dotproduct>.2)
   {
    help.x=-1*tl.x;
    help.y=-1*tl.y;
    help.z=-1*tl.z;
    p1=-2*(norm.x*help.x+norm.y*help.y+norm.z*help.z);
    spot.x=norm.x*p1+help.x;
    spot.y=norm.y*p1+help.y;
    spot.z=norm.z*p1+help.z;
    spot=normalize(spot);
    w2=spot.x*tl.x+spot.y*tl.y+spot.z*tl.z;
    w2=pow(w2,50);
    tcol.r+=list[q]->col.r*sws.col.r*w2;
    tcol.g+=list[q]->col.g*sws.col.r*w2;
    tcol.b+=list[q]->col.b*sws.col.r*w2;
   }
 }
 if(list[q]->wo!=0)
  {
   p1=-2*(norm.x*ray->xdir+norm.y*ray->ydir+norm.z*ray->zdir);
   refl.xdir=norm.x*p1+ray->xdir;
   refl.ydir=norm.y*p1+ray->ydir;
   refl.zdir=norm.z*p1+ray->zdir;
   refl=normalize_p(refl);
   refl.xloc=ray->x;
   refl.yloc=ray->y;
   refl.zloc=ray->z;
   st--;
   if (st<=0)
    st=0;
   else
    if(find(&refl,ray->nr,&r1))
    {
     tcol.r+=list[q]->wo*r1.r/1;
     tcol.g+=list[q]->wo*r1.g/1;
     tcol.b+=list[q]->wo*r1.b/1;
    }
  }
 tcol.r/=1.6666;
 tcol.g/=1.6666;
 tcol.b/=1.6666;

/*
 if(tcol.r>maxcolor)
   tcol.r=maxcolor;
 if(tcol.g>maxcolor)
   tcol.g=maxcolor;
 if(tcol.b>maxcolor)
  tcol.b=maxcolor;
  */
 *rs=tcol;
}

void trace(void)
{
 struct ray start;
 struct color clrp;

 sws.x=64;
 sws.y=320;
 sws.z=124;
 sws.col.r=31;
 sws.col.g=31;
 sws.col.b=31;

 list[0]=&s0;
 list[1]=&s1;
 list[2]=&s2;
 list[3]=&s3;

 start.xloc=0;
 start.yloc=0;
 start.zloc=140;

 s0.x=50;
 s0.y=400;
 s0.z=14;
 s0.r=38;
 s0.r2=s0.r*s0.r;
 s0.col.r=0.3;
 s0.col.g=1;
 s0.col.b=0.3;
 s0.wo=.56;
 s0.type=0;

 s2.x=-50;
 s2.y=400;
 s2.z=14;
 s2.r=38;
 s2.r2=s2.r*s2.r;
 s2.col.r=1;
 s2.col.g=0.3;
 s2.col.b=0.3;
 s2.wo=0.53;
 s2.type=0;

 s3.x=0;
 s3.y=580;
 s3.z=44;
 s3.r=83;
 s3.r2=s3.r*s3.r;
 s3.col.r=0.3;
 s3.col.g=0.3;
 s3.col.b=1;
 s3.wo=0.53;
 s3.type=0;

 s1.a=0;
 s1.b=0;
 s1.c=1.6;
 s1.d=54;
 s1.col.r=0.5;
 s1.col.g=0.5;
 s1.col.b=0;
 s1.wo=0.9;
 s1.type=1;

 for(y=0;y<yres;y++)
  for(x=0;x<xres;x++)
   {
    start.xdir=x-xres/2;
    start.ydir=yres/2/taov*1.1;
    start.zdir=yres/2-y-120;
    start=normalize_p(start);
    st=2;
    clrp.r=0;
    clrp.g=0;
    clrp.b=0;
    st=max_st;
    find(&start,-1,&clrp);
    if (clrp.r>maxcolor)
     clrp.r=maxcolor;
    if (clrp.g>maxcolor)
     clrp.g=maxcolor;
    if (clrp.b>maxcolor)
     clrp.b=maxcolor;
    putpixel(x,y,clrp.r,clrp.g,clrp.b);
  }
}
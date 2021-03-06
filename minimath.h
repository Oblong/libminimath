#pragma once

#include "minimath_generated.h"

// In all the following computations I use the expression obtained before a
// maxima expand(). factorsum()-ing the result doesn't appear to do much.  Doing
// an expand() greatly increases the number of multiplications, but reduces the
// number of additions. In the specific case of a 4x4 symmetric determinant,
// expand() changes (23,40) to (16,58) +,*. 18 more *, but 7 fewer +.
// Session:
/*
(%i13) display2d : false;
(%o13) false

(%i31) sym2 : matrix([m0,m1],
                     [m1,m2]);

(%o31) matrix([m0,m1],[m1,m2])
(%i32) sym3 : matrix([m0,m1,m2],
                     [m1,m3,m4],
                     [m2,m4,m5]);

(%o32) matrix([m0,m1,m2],[m1,m3,m4],[m2,m4,m5])
(%i33) sym4 : matrix([m0,m1,m2,m3],
                     [m1,m4,m5,m6],
                     [m2,m5,m7,m8],
                     [m3,m6,m8,m9]);
(%i99) sym5 : matrix([m0,m1,m2, m3, m4 ],
                     [m1,m5,m6, m7, m8 ],
                     [m2,m6,m9, m10,m11],
                     [m3,m7,m10,m12,m13],
                     [m4,m8,m11,m13,m14]);

(%o99) matrix([m0,m1,m2,m3,m4],[m1,m5,m6,m7,m8],[m2,m6,m9,m10,m11],
              [m3,m7,m10,m12,m13],[m4,m8,m11,m13,m14])

(%i34) determinant(sym4);

(%o34) m0*(m4*(m7*m9-m8^2)-m5*(m5*m9-m6*m8)+m6*(m5*m8-m6*m7))
        -m1*(m1*(m7*m9-m8^2)-m5*(m2*m9-m3*m8)+m6*(m2*m8-m3*m7))
        +m2*(m1*(m5*m9-m6*m8)-m4*(m2*m9-m3*m8)+m6*(m2*m6-m3*m5))
        -m3*(m1*(m5*m8-m6*m7)-m4*(m2*m8-m3*m7)+m5*(m2*m6-m3*m5))
(%i35) expand(determinant(sym4));

(%o35) m0*m4*m7*m9-m1^2*m7*m9-m0*m5^2*m9+2*m1*m2*m5*m9-m2^2*m4*m9-m0*m4*m8^2
                  +m1^2*m8^2+2*m0*m5*m6*m8-2*m1*m2*m6*m8-2*m1*m3*m5*m8
                  +2*m2*m3*m4*m8-m0*m6^2*m7+2*m1*m3*m6*m7-m3^2*m4*m7+m2^2*m6^2
                  -2*m2*m3*m5*m6+m3^2*m5^2
*/

/* The session to compute the determinants appears above. The only postprocessing was to
   replace m.^2 -> m.*m, m. -> m[.]

(%i36) determinant(sym2);

(%o36) m0*m2-m1^2
(%i37) determinant(sym3);

(%o37) m0*(m3*m5-m4^2)-m1*(m1*m5-m2*m4)+m2*(m1*m4-m2*m3)
(%i38) determinant(sym4);

(%o38) m0*(m4*(m7*m9-m8^2)-m5*(m5*m9-m6*m8)+m6*(m5*m8-m6*m7))
        -m1*(m1*(m7*m9-m8^2)-m5*(m2*m9-m3*m8)+m6*(m2*m8-m3*m7))
        +m2*(m1*(m5*m9-m6*m8)-m4*(m2*m9-m3*m8)+m6*(m2*m6-m3*m5))
        -m3*(m1*(m5*m8-m6*m7)-m4*(m2*m8-m3*m7)+m5*(m2*m6-m3*m5))

(%i100) determinant(sym5);

(%o100) -m3*(-m8*((m3*m8-m4*m7)*m9+m2*(m11*m7-m10*m8)-(m11*m3-m10*m4)*m6)
            +m1*(-(m14*m7-m13*m8)*m9+m11*(m11*m7-m10*m8)+(m10*m14-m11*m13)*m6)
            -m5*(-(m14*m3-m13*m4)*m9+m11*(m11*m3-m10*m4)+(m10*m14-m11*m13)*m2)
            +m6*(m11*(m3*m8-m4*m7)+m2*(m14*m7-m13*m8)-(m14*m3-m13*m4)*m6))
         +m4*(-m7*((m3*m8-m4*m7)*m9+m2*(m11*m7-m10*m8)-(m11*m3-m10*m4)*m6)
             +m1*(-(m13*m7-m12*m8)*m9+m10*(m11*m7-m10*m8)
                                     +(m10*m13-m11*m12)*m6)
             -m5*(-(m13*m3-m12*m4)*m9+m10*(m11*m3-m10*m4)
                                     +(m10*m13-m11*m12)*m2)
             +m6*(m10*(m3*m8-m4*m7)+m2*(m13*m7-m12*m8)-(m13*m3-m12*m4)*m6))
         +m0*(m7*(-(m14*m7-m13*m8)*m9+m11*(m11*m7-m10*m8)
                                     +(m10*m14-m11*m13)*m6)
             -m8*(-(m13*m7-m12*m8)*m9+m10*(m11*m7-m10*m8)
                                     +(m10*m13-m11*m12)*m6)
             +m5*((m12*m14-m13^2)*m9-m10*(m10*m14-m11*m13)
                                    +m11*(m10*m13-m11*m12))
             -m6*(-m10*(m14*m7-m13*m8)+m11*(m13*m7-m12*m8)
                                      +(m12*m14-m13^2)*m6))
         -m1*(m7*(-(m14*m3-m13*m4)*m9+m11*(m11*m3-m10*m4)
                                     +(m10*m14-m11*m13)*m2)
             -m8*(-(m13*m3-m12*m4)*m9+m10*(m11*m3-m10*m4)
                                     +(m10*m13-m11*m12)*m2)
             +m1*((m12*m14-m13^2)*m9-m10*(m10*m14-m11*m13)
                                    +m11*(m10*m13-m11*m12))
             -(-m10*(m14*m3-m13*m4)+m11*(m13*m3-m12*m4)+(m12*m14-m13^2)*m2)
              *m6)
         +m2*(m7*(m11*(m3*m8-m4*m7)+m2*(m14*m7-m13*m8)-(m14*m3-m13*m4)*m6)
             -m8*(m10*(m3*m8-m4*m7)+m2*(m13*m7-m12*m8)-(m13*m3-m12*m4)*m6)
             +m1*(-m10*(m14*m7-m13*m8)+m11*(m13*m7-m12*m8)+(m12*m14-m13^2)*m6)
             -(-m10*(m14*m3-m13*m4)+m11*(m13*m3-m12*m4)+(m12*m14-m13^2)*m2)
              *m5)

*/

#if 0
#error You really should be using the cofactors functions below to do this. So far Ive only needed the determinant as a part of computing the inverse, and the below functions do this much more efficiently
static inline double det_sym2(const double* m)
{
  return m[0]*m[2]-m[1]*m[1];
}
static inline double det_sym3(const double* m)
{
  return m[0]*(m[3]*m[5]-m[4]*m[4])-m[1]*(m[1]*m[5]-m[2]*m[4])+m[2]*(m[1]*m[4]-m[2]*m[3]);
}
static inline double det_sym4(const double* m)
{
  return
    +m[0]*(m[4]*(m[7]*m[9]-m[8]*m[8])-m[5]*(m[5]*m[9]-m[6]*m[8])+m[6]*(m[5]*m[8]-m[6]*m[7]))
    -m[1]*(m[1]*(m[7]*m[9]-m[8]*m[8])-m[5]*(m[2]*m[9]-m[3]*m[8])+m[6]*(m[2]*m[8]-m[3]*m[7]))
    +m[2]*(m[1]*(m[5]*m[9]-m[6]*m[8])-m[4]*(m[2]*m[9]-m[3]*m[8])+m[6]*(m[2]*m[6]-m[3]*m[5]))
    -m[3]*(m[1]*(m[5]*m[8]-m[6]*m[7])-m[4]*(m[2]*m[8]-m[3]*m[7])+m[5]*(m[2]*m[6]-m[3]*m[5]));
}
static inline double det_sym5(const double* m)
{
  return
    -m[3]*(-m[8]*((m[3]*m[8]-m[4]*m[7])*m[9]+m[2]*(m[11]*m[7]-m[10]*m[8])-(m[11]*m[3]-m[10]*m[4])*m[6])
           +m[1]*(-(m[14]*m[7]-m[13]*m[8])*m[9]+m[11]*(m[11]*m[7]-m[10]*m[8])+(m[10]*m[14]-m[11]*m[13])*m[6])
           -m[5]*(-(m[14]*m[3]-m[13]*m[4])*m[9]+m[11]*(m[11]*m[3]-m[10]*m[4])+(m[10]*m[14]-m[11]*m[13])*m[2])
           +m[6]*(m[11]*(m[3]*m[8]-m[4]*m[7])+m[2]*(m[14]*m[7]-m[13]*m[8])-(m[14]*m[3]-m[13]*m[4])*m[6]))
    +m[4]*(-m[7]*((m[3]*m[8]-m[4]*m[7])*m[9]+m[2]*(m[11]*m[7]-m[10]*m[8])-(m[11]*m[3]-m[10]*m[4])*m[6])
           +m[1]*(-(m[13]*m[7]-m[12]*m[8])*m[9]+m[10]*(m[11]*m[7]-m[10]*m[8])
                  +(m[10]*m[13]-m[11]*m[12])*m[6])
           -m[5]*(-(m[13]*m[3]-m[12]*m[4])*m[9]+m[10]*(m[11]*m[3]-m[10]*m[4])
                  +(m[10]*m[13]-m[11]*m[12])*m[2])
           +m[6]*(m[10]*(m[3]*m[8]-m[4]*m[7])+m[2]*(m[13]*m[7]-m[12]*m[8])-(m[13]*m[3]-m[12]*m[4])*m[6]))
    +m[0]*(m[7]*(-(m[14]*m[7]-m[13]*m[8])*m[9]+m[11]*(m[11]*m[7]-m[10]*m[8])
                 +(m[10]*m[14]-m[11]*m[13])*m[6])
           -m[8]*(-(m[13]*m[7]-m[12]*m[8])*m[9]+m[10]*(m[11]*m[7]-m[10]*m[8])
                  +(m[10]*m[13]-m[11]*m[12])*m[6])
           +m[5]*((m[12]*m[14]-m[13]*m[13])*m[9]-m[10]*(m[10]*m[14]-m[11]*m[13])
                  +m[11]*(m[10]*m[13]-m[11]*m[12]))
           -m[6]*(-m[10]*(m[14]*m[7]-m[13]*m[8])+m[11]*(m[13]*m[7]-m[12]*m[8])
                  +(m[12]*m[14]-m[13]*m[13])*m[6]))
    -m[1]*(m[7]*(-(m[14]*m[3]-m[13]*m[4])*m[9]+m[11]*(m[11]*m[3]-m[10]*m[4])
                 +(m[10]*m[14]-m[11]*m[13])*m[2])
           -m[8]*(-(m[13]*m[3]-m[12]*m[4])*m[9]+m[10]*(m[11]*m[3]-m[10]*m[4])
                  +(m[10]*m[13]-m[11]*m[12])*m[2])
           +m[1]*((m[12]*m[14]-m[13]*m[13])*m[9]-m[10]*(m[10]*m[14]-m[11]*m[13])
                  +m[11]*(m[10]*m[13]-m[11]*m[12]))
           -(-m[10]*(m[14]*m[3]-m[13]*m[4])+m[11]*(m[13]*m[3]-m[12]*m[4])+(m[12]*m[14]-m[13]*m[13])*m[2])
           *m[6])
    +m[2]*(m[7]*(m[11]*(m[3]*m[8]-m[4]*m[7])+m[2]*(m[14]*m[7]-m[13]*m[8])-(m[14]*m[3]-m[13]*m[4])*m[6])
           -m[8]*(m[10]*(m[3]*m[8]-m[4]*m[7])+m[2]*(m[13]*m[7]-m[12]*m[8])-(m[13]*m[3]-m[12]*m[4])*m[6])
           +m[1]*(-m[10]*(m[14]*m[7]-m[13]*m[8])+m[11]*(m[13]*m[7]-m[12]*m[8])+(m[12]*m[14]-m[13]*m[13])*m[6])
           -(-m[10]*(m[14]*m[3]-m[13]*m[4])+m[11]*(m[13]*m[3]-m[12]*m[4])+(m[12]*m[14]-m[13]*m[13])*m[2])
           *m[5]);
}
#endif

/* I now do inverses. I return transposed cofactors. Original matrix * cofactors / det = identity
As before, I replaced  m.^2 -> m.*m, m. -> m[.]
I also removed the lower triangle, since I'm dealing with symmetric matrices here
Session:


(%i64) num( ev(invert(sym2),detout) );

(%o64) matrix([m2,-m1],[-m1,m0])
(%i65) num( ev(invert(sym3),detout) );

(%o65) matrix([m3*m5-m4^2,m2*m4-m1*m5,m1*m4-m2*m3],
              [m2*m4-m1*m5,m0*m5-m2^2,m1*m2-m0*m4],
              [m1*m4-m2*m3,m1*m2-m0*m4,m0*m3-m1^2])
(%i66) num( ev(invert(sym4),detout) );

(%o66) matrix([m4*(m7*m9-m8^2)-m5*(m5*m9-m6*m8)+m6*(m5*m8-m6*m7),
               -m1*(m7*m9-m8^2)+m2*(m5*m9-m6*m8)-m3*(m5*m8-m6*m7),
               m1*(m5*m9-m6*m8)-m2*(m4*m9-m6^2)+m3*(m4*m8-m5*m6),
               -m1*(m5*m8-m6*m7)+m2*(m4*m8-m5*m6)-m3*(m4*m7-m5^2)],
              [-m1*(m7*m9-m8^2)+m5*(m2*m9-m3*m8)-m6*(m2*m8-m3*m7),
               m0*(m7*m9-m8^2)-m2*(m2*m9-m3*m8)+m3*(m2*m8-m3*m7),
               -m0*(m5*m9-m6*m8)+m2*(m1*m9-m3*m6)-m3*(m1*m8-m3*m5),
               m0*(m5*m8-m6*m7)-m2*(m1*m8-m2*m6)+m3*(m1*m7-m2*m5)],
              [m1*(m5*m9-m6*m8)-m4*(m2*m9-m3*m8)+m6*(m2*m6-m3*m5),
               -m0*(m5*m9-m6*m8)+m1*(m2*m9-m3*m8)-m3*(m2*m6-m3*m5),
               m0*(m4*m9-m6^2)-m1*(m1*m9-m3*m6)+m3*(m1*m6-m3*m4),
               -m0*(m4*m8-m5*m6)+m1*(m1*m8-m2*m6)-m3*(m1*m5-m2*m4)],
              [-m1*(m5*m8-m6*m7)+m4*(m2*m8-m3*m7)-m5*(m2*m6-m3*m5),
               m0*(m5*m8-m6*m7)-m1*(m2*m8-m3*m7)+m2*(m2*m6-m3*m5),
               -m0*(m4*m8-m5*m6)+m1*(m1*m8-m3*m5)-m2*(m1*m6-m3*m4),
               m0*(m4*m7-m5^2)-m1*(m1*m7-m2*m5)+m2*(m1*m5-m2*m4)])
(%i103) num( ev(invert(sym5),detout) );

(%o103) matrix([m7*(-(m14*m7-m13*m8)*m9+m11*(m11*m7-m10*m8)
                                       +(m10*m14-m11*m13)*m6)
                 -m8*(-(m13*m7-m12*m8)*m9+m10*(m11*m7-m10*m8)
                                         +(m10*m13-m11*m12)*m6)
                 +m5*((m12*m14-m13^2)*m9-m10*(m10*m14-m11*m13)
                                        +m11*(m10*m13-m11*m12))
                 -m6*(-m10*(m14*m7-m13*m8)+m11*(m13*m7-m12*m8)
                                          +(m12*m14-m13^2)*m6),
                -m3*(-(m14*m7-m13*m8)*m9+m11*(m11*m7-m10*m8)
                                        +(m10*m14-m11*m13)*m6)
                 +m4*(-(m13*m7-m12*m8)*m9+m10*(m11*m7-m10*m8)
                                         +(m10*m13-m11*m12)*m6)
                 -m1*((m12*m14-m13^2)*m9-m10*(m10*m14-m11*m13)
                                        +m11*(m10*m13-m11*m12))
                 +m2*(-m10*(m14*m7-m13*m8)+m11*(m13*m7-m12*m8)
                                          +(m12*m14-m13^2)*m6),
                -m2*(-m7*(m14*m7-m13*m8)+m8*(m13*m7-m12*m8)
                                        +(m12*m14-m13^2)*m5)
                 +m3*(-m6*(m14*m7-m13*m8)+m8*(m11*m7-m10*m8)
                                         +(m10*m14-m11*m13)*m5)
                 -m4*(-m6*(m13*m7-m12*m8)+m7*(m11*m7-m10*m8)
                                         +(m10*m13-m11*m12)*m5)
                 +m1*((m10*m13-m11*m12)*m8-(m10*m14-m11*m13)*m7
                                          +(m12*m14-m13^2)*m6),
                -m3*(m8*(m11*m6-m8*m9)+m5*(m14*m9-m11^2)-m6*(m14*m6-m11*m8))
                 +m4*(m7*(m11*m6-m8*m9)+m5*(m13*m9-m10*m11)
                                       -m6*(m13*m6-m10*m8))
                 -m1*(-m7*(m14*m9-m11^2)+m8*(m13*m9-m10*m11)
                                        +(m10*m14-m11*m13)*m6)
                 +m2*(-m7*(m14*m6-m11*m8)+m8*(m13*m6-m10*m8)
                                         +(m10*m14-m11*m13)*m5),
                m3*(m8*(m10*m6-m7*m9)+m5*(m13*m9-m10*m11)-m6*(m13*m6-m11*m7))
                 -m4*(m7*(m10*m6-m7*m9)+m5*(m12*m9-m10^2)-m6*(m12*m6-m10*m7))
                 +m1*(-m7*(m13*m9-m10*m11)+m8*(m12*m9-m10^2)
                                          +(m10*m13-m11*m12)*m6)
                 -m2*((m12*m6-m10*m7)*m8-m7*(m13*m6-m11*m7)
                                        +(m10*m13-m11*m12)*m5)],
               [-m7*(-(m14*m3-m13*m4)*m9+m11*(m11*m3-m10*m4)
                                        +(m10*m14-m11*m13)*m2)
                 +m8*(-(m13*m3-m12*m4)*m9+m10*(m11*m3-m10*m4)
                                         +(m10*m13-m11*m12)*m2)
                 -m1*((m12*m14-m13^2)*m9-m10*(m10*m14-m11*m13)
                                        +m11*(m10*m13-m11*m12))
                 +(-m10*(m14*m3-m13*m4)+m11*(m13*m3-m12*m4)
                                       +(m12*m14-m13^2)*m2)
                  *m6,
                m3*(-(m14*m3-m13*m4)*m9+m11*(m11*m3-m10*m4)
                                       +(m10*m14-m11*m13)*m2)
                 -m4*(-(m13*m3-m12*m4)*m9+m10*(m11*m3-m10*m4)
                                         +(m10*m13-m11*m12)*m2)
                 +m0*((m12*m14-m13^2)*m9-m10*(m10*m14-m11*m13)
                                        +m11*(m10*m13-m11*m12))
                 -m2*(-m10*(m14*m3-m13*m4)+m11*(m13*m3-m12*m4)
                                          +(m12*m14-m13^2)*m2),
                m2*((m13*m3-m12*m4)*m8-(m14*m3-m13*m4)*m7+m1*(m12*m14-m13^2))
                 -m3*((m11*m3-m10*m4)*m8-(m14*m3-m13*m4)*m6
                                        +m1*(m10*m14-m11*m13))
                 -m0*((m10*m13-m11*m12)*m8-(m10*m14-m11*m13)*m7
                                          +(m12*m14-m13^2)*m6)
                 +m4*((m11*m3-m10*m4)*m7-(m13*m3-m12*m4)*m6
                                        +m1*(m10*m13-m11*m12)),
                m3*(m8*(m11*m2-m4*m9)+m1*(m14*m9-m11^2)-(m14*m2-m11*m4)*m6)
                 -m4*(m7*(m11*m2-m4*m9)+m1*(m13*m9-m10*m11)
                                       -(m13*m2-m10*m4)*m6)
                 +m0*(-m7*(m14*m9-m11^2)+m8*(m13*m9-m10*m11)
                                        +(m10*m14-m11*m13)*m6)
                 -m2*((m13*m2-m10*m4)*m8-(m14*m2-m11*m4)*m7
                                        +m1*(m10*m14-m11*m13)),
                -m3*(m8*(m10*m2-m3*m9)+m1*(m13*m9-m10*m11)-(m13*m2-m11*m3)*m6)
                 +m4*(m7*(m10*m2-m3*m9)+m1*(m12*m9-m10^2)-(m12*m2-m10*m3)*m6)
                 -m0*(-m7*(m13*m9-m10*m11)+m8*(m12*m9-m10^2)
                                          +(m10*m13-m11*m12)*m6)
                 +m2*((m12*m2-m10*m3)*m8-(m13*m2-m11*m3)*m7
                                        +m1*(m10*m13-m11*m12))],
               [m7*(m11*(m3*m8-m4*m7)+m2*(m14*m7-m13*m8)-(m14*m3-m13*m4)*m6)
                 -m8*(m10*(m3*m8-m4*m7)+m2*(m13*m7-m12*m8)-(m13*m3-m12*m4)*m6)
                 +m1*(-m10*(m14*m7-m13*m8)+m11*(m13*m7-m12*m8)
                                          +(m12*m14-m13^2)*m6)
                 -(-m10*(m14*m3-m13*m4)+m11*(m13*m3-m12*m4)
                                       +(m12*m14-m13^2)*m2)
                  *m5,
                -m3*(m11*(m3*m8-m4*m7)+m2*(m14*m7-m13*m8)-(m14*m3-m13*m4)*m6)
                 +m4*(m10*(m3*m8-m4*m7)+m2*(m13*m7-m12*m8)-(m13*m3-m12*m4)*m6)
                 -m0*(-m10*(m14*m7-m13*m8)+m11*(m13*m7-m12*m8)
                                          +(m12*m14-m13^2)*m6)
                 +m1*(-m10*(m14*m3-m13*m4)+m11*(m13*m3-m12*m4)
                                          +(m12*m14-m13^2)*m2),
                m3*(m8*(m3*m8-m4*m7)+m1*(m14*m7-m13*m8)-(m14*m3-m13*m4)*m5)
                 -m4*(m7*(m3*m8-m4*m7)+m1*(m13*m7-m12*m8)-(m13*m3-m12*m4)*m5)
                 +m0*(-m7*(m14*m7-m13*m8)+m8*(m13*m7-m12*m8)
                                         +(m12*m14-m13^2)*m5)
                 -m1*((m13*m3-m12*m4)*m8-(m14*m3-m13*m4)*m7
                                        +m1*(m12*m14-m13^2)),
                -m3*(m8*(m2*m8-m4*m6)+m1*(m14*m6-m11*m8)-(m14*m2-m11*m4)*m5)
                 +m4*(m7*(m2*m8-m4*m6)+m1*(m13*m6-m10*m8)-(m13*m2-m10*m4)*m5)
                 -m0*(-m7*(m14*m6-m11*m8)+m8*(m13*m6-m10*m8)
                                         +(m10*m14-m11*m13)*m5)
                 +m1*((m13*m2-m10*m4)*m8-(m14*m2-m11*m4)*m7
                                        +m1*(m10*m14-m11*m13)),
                m3*((m2*m7-m3*m6)*m8+m1*(m13*m6-m11*m7)-(m13*m2-m11*m3)*m5)
                 +m0*((m12*m6-m10*m7)*m8-m7*(m13*m6-m11*m7)
                                        +(m10*m13-m11*m12)*m5)
                 -m1*((m12*m2-m10*m3)*m8-(m13*m2-m11*m3)*m7
                                        +m1*(m10*m13-m11*m12))
                 -m4*(m7*(m2*m7-m3*m6)+m1*(m12*m6-m10*m7)
                                      -(m12*m2-m10*m3)*m5)],
               [m8*((m3*m8-m4*m7)*m9+m2*(m11*m7-m10*m8)-(m11*m3-m10*m4)*m6)
                 -m1*(-(m14*m7-m13*m8)*m9+m11*(m11*m7-m10*m8)
                                         +(m10*m14-m11*m13)*m6)
                 +m5*(-(m14*m3-m13*m4)*m9+m11*(m11*m3-m10*m4)
                                         +(m10*m14-m11*m13)*m2)
                 -m6*(m11*(m3*m8-m4*m7)+m2*(m14*m7-m13*m8)
                                       -(m14*m3-m13*m4)*m6),
                -m4*((m3*m8-m4*m7)*m9+m2*(m11*m7-m10*m8)-(m11*m3-m10*m4)*m6)
                 +m0*(-(m14*m7-m13*m8)*m9+m11*(m11*m7-m10*m8)
                                         +(m10*m14-m11*m13)*m6)
                 -m1*(-(m14*m3-m13*m4)*m9+m11*(m11*m3-m10*m4)
                                         +(m10*m14-m11*m13)*m2)
                 +m2*(m11*(m3*m8-m4*m7)+m2*(m14*m7-m13*m8)
                                       -(m14*m3-m13*m4)*m6),
                -m2*(m8*(m3*m8-m4*m7)+m1*(m14*m7-m13*m8)-(m14*m3-m13*m4)*m5)
                 +m4*(m6*(m3*m8-m4*m7)+m1*(m11*m7-m10*m8)-(m11*m3-m10*m4)*m5)
                 -m0*(-m6*(m14*m7-m13*m8)+m8*(m11*m7-m10*m8)
                                         +(m10*m14-m11*m13)*m5)
                 +m1*((m11*m3-m10*m4)*m8-(m14*m3-m13*m4)*m6
                                        +m1*(m10*m14-m11*m13)),
                m0*(m8*(m11*m6-m8*m9)+m5*(m14*m9-m11^2)-m6*(m14*m6-m11*m8))
                 -m4*(m1*(m11*m6-m8*m9)-m5*(m11*m2-m4*m9)+m6*(m2*m8-m4*m6))
                 -m1*(m8*(m11*m2-m4*m9)+m1*(m14*m9-m11^2)-(m14*m2-m11*m4)*m6)
                 +m2*(m8*(m2*m8-m4*m6)+m1*(m14*m6-m11*m8)-(m14*m2-m11*m4)*m5),
                -m0*(m8*(m10*m6-m7*m9)+m5*(m13*m9-m10*m11)-m6*(m13*m6-m11*m7))
                 +m4*(m1*(m10*m6-m7*m9)-m5*(m10*m2-m3*m9)+m6*(m2*m7-m3*m6))
                 +m1*(m8*(m10*m2-m3*m9)+m1*(m13*m9-m10*m11)
                                       -(m13*m2-m11*m3)*m6)
                 -m2*((m2*m7-m3*m6)*m8+m1*(m13*m6-m11*m7)
                                      -(m13*m2-m11*m3)*m5)],
               [-m7*((m3*m8-m4*m7)*m9+m2*(m11*m7-m10*m8)-(m11*m3-m10*m4)*m6)
                 +m1*(-(m13*m7-m12*m8)*m9+m10*(m11*m7-m10*m8)
                                         +(m10*m13-m11*m12)*m6)
                 -m5*(-(m13*m3-m12*m4)*m9+m10*(m11*m3-m10*m4)
                                         +(m10*m13-m11*m12)*m2)
                 +m6*(m10*(m3*m8-m4*m7)+m2*(m13*m7-m12*m8)
                                       -(m13*m3-m12*m4)*m6),
                m3*((m3*m8-m4*m7)*m9+m2*(m11*m7-m10*m8)-(m11*m3-m10*m4)*m6)
                 -m0*(-(m13*m7-m12*m8)*m9+m10*(m11*m7-m10*m8)
                                         +(m10*m13-m11*m12)*m6)
                 +m1*(-(m13*m3-m12*m4)*m9+m10*(m11*m3-m10*m4)
                                         +(m10*m13-m11*m12)*m2)
                 -m2*(m10*(m3*m8-m4*m7)+m2*(m13*m7-m12*m8)
                                       -(m13*m3-m12*m4)*m6),
                m2*(m7*(m3*m8-m4*m7)+m1*(m13*m7-m12*m8)-(m13*m3-m12*m4)*m5)
                 -m3*(m6*(m3*m8-m4*m7)+m1*(m11*m7-m10*m8)-(m11*m3-m10*m4)*m5)
                 +m0*(-m6*(m13*m7-m12*m8)+m7*(m11*m7-m10*m8)
                                         +(m10*m13-m11*m12)*m5)
                 -m1*((m11*m3-m10*m4)*m7-(m13*m3-m12*m4)*m6
                                        +m1*(m10*m13-m11*m12)),
                -m0*(m7*(m11*m6-m8*m9)+m5*(m13*m9-m10*m11)-m6*(m13*m6-m10*m8))
                 +m3*(m1*(m11*m6-m8*m9)-m5*(m11*m2-m4*m9)+m6*(m2*m8-m4*m6))
                 +m1*(m7*(m11*m2-m4*m9)+m1*(m13*m9-m10*m11)
                                       -(m13*m2-m10*m4)*m6)
                 -m2*(m7*(m2*m8-m4*m6)+m1*(m13*m6-m10*m8)-(m13*m2-m10*m4)*m5),
                m0*(m7*(m10*m6-m7*m9)+m5*(m12*m9-m10^2)-m6*(m12*m6-m10*m7))
                 -m3*(m1*(m10*m6-m7*m9)-m5*(m10*m2-m3*m9)+m6*(m2*m7-m3*m6))
                 -m1*(m7*(m10*m2-m3*m9)+m1*(m12*m9-m10^2)-(m12*m2-m10*m3)*m6)
                 +m2*(m7*(m2*m7-m3*m6)+m1*(m12*m6-m10*m7)
                                      -(m12*m2-m10*m3)*m5)])
*/

static inline double cofactors_sym2(const double* restrict m, double* restrict c)
{
  c[0] = m[2];
  c[1] = -m[1];
  c[2] = -m[1];

  return m[0]*c[0] + m[1]*c[1];
}

static inline double cofactors_sym3(const double* restrict m, double* restrict c)
{
  c[0] = m[3]*m[5]-m[4]*m[4];
  c[1] = m[2]*m[4]-m[1]*m[5];
  c[2] = m[1]*m[4]-m[2]*m[3];
  c[3] = m[0]*m[5]-m[2]*m[2];
  c[4] = m[1]*m[2]-m[0]*m[4];
  c[5] = m[0]*m[3]-m[1]*m[1];

  return m[0]*c[0] + m[1]*c[1] + m[2]*c[2];
}

static inline double cofactors_sym4(const double* restrict m, double* restrict c)
{
  c[0] = m[4]*(m[7]*m[9]-m[8]*m[8])-m[5]*(m[5]*m[9]-m[6]*m[8])+m[6]*(m[5]*m[8]-m[6]*m[7]);
  c[1] = -m[1]*(m[7]*m[9]-m[8]*m[8])+m[2]*(m[5]*m[9]-m[6]*m[8])-m[3]*(m[5]*m[8]-m[6]*m[7]);
  c[2] = m[1]*(m[5]*m[9]-m[6]*m[8])-m[2]*(m[4]*m[9]-m[6]*m[6])+m[3]*(m[4]*m[8]-m[5]*m[6]);
  c[3] = -m[1]*(m[5]*m[8]-m[6]*m[7])+m[2]*(m[4]*m[8]-m[5]*m[6])-m[3]*(m[4]*m[7]-m[5]*m[5]);
  c[4] = m[0]*(m[7]*m[9]-m[8]*m[8])-m[2]*(m[2]*m[9]-m[3]*m[8])+m[3]*(m[2]*m[8]-m[3]*m[7]);
  c[5] = -m[0]*(m[5]*m[9]-m[6]*m[8])+m[2]*(m[1]*m[9]-m[3]*m[6])-m[3]*(m[1]*m[8]-m[3]*m[5]);
  c[6] = m[0]*(m[5]*m[8]-m[6]*m[7])-m[2]*(m[1]*m[8]-m[2]*m[6])+m[3]*(m[1]*m[7]-m[2]*m[5]);
  c[7] = m[0]*(m[4]*m[9]-m[6]*m[6])-m[1]*(m[1]*m[9]-m[3]*m[6])+m[3]*(m[1]*m[6]-m[3]*m[4]);
  c[8] = -m[0]*(m[4]*m[8]-m[5]*m[6])+m[1]*(m[1]*m[8]-m[2]*m[6])-m[3]*(m[1]*m[5]-m[2]*m[4]);
  c[9] = m[0]*(m[4]*m[7]-m[5]*m[5])-m[1]*(m[1]*m[7]-m[2]*m[5])+m[2]*(m[1]*m[5]-m[2]*m[4]);

  return m[0]*c[0] + m[1]*c[1] + m[2]*c[2] + m[3]*c[3];
}

static inline double cofactors_sym5(const double* restrict m, double* restrict c)
{
  c[0] =   m[7]*(-(m[14]*m[7]-m[13]*m[8])*m[9]+m[11]*(m[11]*m[7]-m[10]*m[8])+(m[10]*m[14]-m[11]*m[13])*m[6])-m[8]*(-(m[13]*m[7]-m[12]*m[8])*m[9]+m[10]*(m[11]*m[7]-m[10]*m[8])+(m[10]*m[13]-m[11]*m[12])*m[6])+m[5]*((m[12]*m[14]-m[13]*m[13])*m[9]-m[10]*(m[10]*m[14]-m[11]*m[13])+m[11]*(m[10]*m[13]-m[11]*m[12]))-m[6]*(-m[10]*(m[14]*m[7]-m[13]*m[8])+m[11]*(m[13]*m[7]-m[12]*m[8])+(m[12]*m[14]-m[13]*m[13])*m[6]);
  c[1] =   -m[3]*(-(m[14]*m[7]-m[13]*m[8])*m[9]+m[11]*(m[11]*m[7]-m[10]*m[8])+(m[10]*m[14]-m[11]*m[13])*m[6])+m[4]*(-(m[13]*m[7]-m[12]*m[8])*m[9]+m[10]*(m[11]*m[7]-m[10]*m[8])+(m[10]*m[13]-m[11]*m[12])*m[6])-m[1]*((m[12]*m[14]-m[13]*m[13])*m[9]-m[10]*(m[10]*m[14]-m[11]*m[13])+m[11]*(m[10]*m[13]-m[11]*m[12]))+m[2]*(-m[10]*(m[14]*m[7]-m[13]*m[8])+m[11]*(m[13]*m[7]-m[12]*m[8])+(m[12]*m[14]-m[13]*m[13])*m[6]);
  c[2] =   -m[2]*(-m[7]*(m[14]*m[7]-m[13]*m[8])+m[8]*(m[13]*m[7]-m[12]*m[8])+(m[12]*m[14]-m[13]*m[13])*m[5])+m[3]*(-m[6]*(m[14]*m[7]-m[13]*m[8])+m[8]*(m[11]*m[7]-m[10]*m[8])+(m[10]*m[14]-m[11]*m[13])*m[5])-m[4]*(-m[6]*(m[13]*m[7]-m[12]*m[8])+m[7]*(m[11]*m[7]-m[10]*m[8])+(m[10]*m[13]-m[11]*m[12])*m[5])+m[1]*((m[10]*m[13]-m[11]*m[12])*m[8]-(m[10]*m[14]-m[11]*m[13])*m[7]+(m[12]*m[14]-m[13]*m[13])*m[6]);
  c[3] =   -m[3]*(m[8]*(m[11]*m[6]-m[8]*m[9])+m[5]*(m[14]*m[9]-m[11]*m[11])-m[6]*(m[14]*m[6]-m[11]*m[8]))+m[4]*(m[7]*(m[11]*m[6]-m[8]*m[9])+m[5]*(m[13]*m[9]-m[10]*m[11])-m[6]*(m[13]*m[6]-m[10]*m[8]))-m[1]*(-m[7]*(m[14]*m[9]-m[11]*m[11])+m[8]*(m[13]*m[9]-m[10]*m[11])+(m[10]*m[14]-m[11]*m[13])*m[6])+m[2]*(-m[7]*(m[14]*m[6]-m[11]*m[8])+m[8]*(m[13]*m[6]-m[10]*m[8])+(m[10]*m[14]-m[11]*m[13])*m[5]);
  c[4] =   m[3]*(m[8]*(m[10]*m[6]-m[7]*m[9])+m[5]*(m[13]*m[9]-m[10]*m[11])-m[6]*(m[13]*m[6]-m[11]*m[7]))-m[4]*(m[7]*(m[10]*m[6]-m[7]*m[9])+m[5]*(m[12]*m[9]-m[10]*m[10])-m[6]*(m[12]*m[6]-m[10]*m[7]))+m[1]*(-m[7]*(m[13]*m[9]-m[10]*m[11])+m[8]*(m[12]*m[9]-m[10]*m[10])+(m[10]*m[13]-m[11]*m[12])*m[6])-m[2]*((m[12]*m[6]-m[10]*m[7])*m[8]-m[7]*(m[13]*m[6]-m[11]*m[7])+(m[10]*m[13]-m[11]*m[12])*m[5]);
  c[5] =   m[3]*(-(m[14]*m[3]-m[13]*m[4])*m[9]+m[11]*(m[11]*m[3]-m[10]*m[4])+(m[10]*m[14]-m[11]*m[13])*m[2])-m[4]*(-(m[13]*m[3]-m[12]*m[4])*m[9]+m[10]*(m[11]*m[3]-m[10]*m[4])+(m[10]*m[13]-m[11]*m[12])*m[2])+m[0]*((m[12]*m[14]-m[13]*m[13])*m[9]-m[10]*(m[10]*m[14]-m[11]*m[13])+m[11]*(m[10]*m[13]-m[11]*m[12]))-m[2]*(-m[10]*(m[14]*m[3]-m[13]*m[4])+m[11]*(m[13]*m[3]-m[12]*m[4])+(m[12]*m[14]-m[13]*m[13])*m[2]);
  c[6] =   m[2]*((m[13]*m[3]-m[12]*m[4])*m[8]-(m[14]*m[3]-m[13]*m[4])*m[7]+m[1]*(m[12]*m[14]-m[13]*m[13]))-m[3]*((m[11]*m[3]-m[10]*m[4])*m[8]-(m[14]*m[3]-m[13]*m[4])*m[6]+m[1]*(m[10]*m[14]-m[11]*m[13]))-m[0]*((m[10]*m[13]-m[11]*m[12])*m[8]-(m[10]*m[14]-m[11]*m[13])*m[7]+(m[12]*m[14]-m[13]*m[13])*m[6])+m[4]*((m[11]*m[3]-m[10]*m[4])*m[7]-(m[13]*m[3]-m[12]*m[4])*m[6]+m[1]*(m[10]*m[13]-m[11]*m[12]));
  c[7] =   m[3]*(m[8]*(m[11]*m[2]-m[4]*m[9])+m[1]*(m[14]*m[9]-m[11]*m[11])-(m[14]*m[2]-m[11]*m[4])*m[6])-m[4]*(m[7]*(m[11]*m[2]-m[4]*m[9])+m[1]*(m[13]*m[9]-m[10]*m[11])-(m[13]*m[2]-m[10]*m[4])*m[6])+m[0]*(-m[7]*(m[14]*m[9]-m[11]*m[11])+m[8]*(m[13]*m[9]-m[10]*m[11])+(m[10]*m[14]-m[11]*m[13])*m[6])-m[2]*((m[13]*m[2]-m[10]*m[4])*m[8]-(m[14]*m[2]-m[11]*m[4])*m[7]+m[1]*(m[10]*m[14]-m[11]*m[13]));
  c[8] =   -m[3]*(m[8]*(m[10]*m[2]-m[3]*m[9])+m[1]*(m[13]*m[9]-m[10]*m[11])-(m[13]*m[2]-m[11]*m[3])*m[6])+m[4]*(m[7]*(m[10]*m[2]-m[3]*m[9])+m[1]*(m[12]*m[9]-m[10]*m[10])-(m[12]*m[2]-m[10]*m[3])*m[6])-m[0]*(-m[7]*(m[13]*m[9]-m[10]*m[11])+m[8]*(m[12]*m[9]-m[10]*m[10])+(m[10]*m[13]-m[11]*m[12])*m[6])+m[2]*((m[12]*m[2]-m[10]*m[3])*m[8]-(m[13]*m[2]-m[11]*m[3])*m[7]+m[1]*(m[10]*m[13]-m[11]*m[12]));
  c[9] =   m[3]*(m[8]*(m[3]*m[8]-m[4]*m[7])+m[1]*(m[14]*m[7]-m[13]*m[8])-(m[14]*m[3]-m[13]*m[4])*m[5])-m[4]*(m[7]*(m[3]*m[8]-m[4]*m[7])+m[1]*(m[13]*m[7]-m[12]*m[8])-(m[13]*m[3]-m[12]*m[4])*m[5])+m[0]*(-m[7]*(m[14]*m[7]-m[13]*m[8])+m[8]*(m[13]*m[7]-m[12]*m[8])+(m[12]*m[14]-m[13]*m[13])*m[5])-m[1]*((m[13]*m[3]-m[12]*m[4])*m[8]-(m[14]*m[3]-m[13]*m[4])*m[7]+m[1]*(m[12]*m[14]-m[13]*m[13]));
  c[10] =   -m[3]*(m[8]*(m[2]*m[8]-m[4]*m[6])+m[1]*(m[14]*m[6]-m[11]*m[8])-(m[14]*m[2]-m[11]*m[4])*m[5])+m[4]*(m[7]*(m[2]*m[8]-m[4]*m[6])+m[1]*(m[13]*m[6]-m[10]*m[8])-(m[13]*m[2]-m[10]*m[4])*m[5])-m[0]*(-m[7]*(m[14]*m[6]-m[11]*m[8])+m[8]*(m[13]*m[6]-m[10]*m[8])+(m[10]*m[14]-m[11]*m[13])*m[5])+m[1]*((m[13]*m[2]-m[10]*m[4])*m[8]-(m[14]*m[2]-m[11]*m[4])*m[7]+m[1]*(m[10]*m[14]-m[11]*m[13]));
  c[11] =   m[3]*((m[2]*m[7]-m[3]*m[6])*m[8]+m[1]*(m[13]*m[6]-m[11]*m[7])-(m[13]*m[2]-m[11]*m[3])*m[5])+m[0]*((m[12]*m[6]-m[10]*m[7])*m[8]-m[7]*(m[13]*m[6]-m[11]*m[7])+(m[10]*m[13]-m[11]*m[12])*m[5])-m[1]*((m[12]*m[2]-m[10]*m[3])*m[8]-(m[13]*m[2]-m[11]*m[3])*m[7]+m[1]*(m[10]*m[13]-m[11]*m[12]))-m[4]*(m[7]*(m[2]*m[7]-m[3]*m[6])+m[1]*(m[12]*m[6]-m[10]*m[7])-(m[12]*m[2]-m[10]*m[3])*m[5]);
  c[12] =   m[0]*(m[8]*(m[11]*m[6]-m[8]*m[9])+m[5]*(m[14]*m[9]-m[11]*m[11])-m[6]*(m[14]*m[6]-m[11]*m[8]))-m[4]*(m[1]*(m[11]*m[6]-m[8]*m[9])-m[5]*(m[11]*m[2]-m[4]*m[9])+m[6]*(m[2]*m[8]-m[4]*m[6]))-m[1]*(m[8]*(m[11]*m[2]-m[4]*m[9])+m[1]*(m[14]*m[9]-m[11]*m[11])-(m[14]*m[2]-m[11]*m[4])*m[6])+m[2]*(m[8]*(m[2]*m[8]-m[4]*m[6])+m[1]*(m[14]*m[6]-m[11]*m[8])-(m[14]*m[2]-m[11]*m[4])*m[5]);
  c[13] =   -m[0]*(m[8]*(m[10]*m[6]-m[7]*m[9])+m[5]*(m[13]*m[9]-m[10]*m[11])-m[6]*(m[13]*m[6]-m[11]*m[7]))+m[4]*(m[1]*(m[10]*m[6]-m[7]*m[9])-m[5]*(m[10]*m[2]-m[3]*m[9])+m[6]*(m[2]*m[7]-m[3]*m[6]))+m[1]*(m[8]*(m[10]*m[2]-m[3]*m[9])+m[1]*(m[13]*m[9]-m[10]*m[11])-(m[13]*m[2]-m[11]*m[3])*m[6])-m[2]*((m[2]*m[7]-m[3]*m[6])*m[8]+m[1]*(m[13]*m[6]-m[11]*m[7])-(m[13]*m[2]-m[11]*m[3])*m[5]);
  c[14] =   m[0]*(m[7]*(m[10]*m[6]-m[7]*m[9])+m[5]*(m[12]*m[9]-m[10]*m[10])-m[6]*(m[12]*m[6]-m[10]*m[7]))-m[3]*(m[1]*(m[10]*m[6]-m[7]*m[9])-m[5]*(m[10]*m[2]-m[3]*m[9])+m[6]*(m[2]*m[7]-m[3]*m[6]))-m[1]*(m[7]*(m[10]*m[2]-m[3]*m[9])+m[1]*(m[12]*m[9]-m[10]*m[10])-(m[12]*m[2]-m[10]*m[3])*m[6])+m[2]*(m[7]*(m[2]*m[7]-m[3]*m[6])+m[1]*(m[12]*m[6]-m[10]*m[7])-(m[12]*m[2]-m[10]*m[3])*m[5]);

  return m[0]*c[0] + m[1]*c[1] + m[2]*c[2] + m[3]*c[3] + m[4]*c[4];
}

# warning I should get rid of mul_sym33_sym33_scaled_out
// symmetrix 3x3 by symmetrix 3x3, written into a new non-symmetric matrix, scaled
static inline void mul_sym33_sym33_scaled_out(const double* restrict s0, const double* restrict s1, double* restrict mout, double scale)
{
// (%i106) matrix([m0_0,m0_1,m0_2],
//                [m0_1,m0_3,m0_4],
//                [m0_2,m0_4,m0_5]) .
//         matrix([m1_0,m1_1,m1_2],
//                [m1_1,m1_3,m1_4],
//                [m1_2,m1_4,m1_5]);

// (%o106) matrix([m0_2*m1_2+m0_1*m1_1+m0_0*m1_0,m0_2*m1_4+m0_1*m1_3+m0_0*m1_1,
//                 m0_2*m1_5+m0_1*m1_4+m0_0*m1_2],
//                [m0_4*m1_2+m0_3*m1_1+m0_1*m1_0,m0_4*m1_4+m0_3*m1_3+m0_1*m1_1,
//                 m0_4*m1_5+m0_3*m1_4+m0_1*m1_2],
//                [m0_5*m1_2+m0_4*m1_1+m0_2*m1_0,m0_5*m1_4+m0_4*m1_3+m0_2*m1_1,
//                 m0_5*m1_5+m0_4*m1_4+m0_2*m1_2])

  mout[0] = scale * (s0[2]*s1[2]+s0[1]*s1[1]+s0[0]*s1[0]);
  mout[1] = scale * (s0[2]*s1[4]+s0[1]*s1[3]+s0[0]*s1[1]);
  mout[2] = scale * (s0[2]*s1[5]+s0[1]*s1[4]+s0[0]*s1[2]);
  mout[3] = scale * (s0[4]*s1[2]+s0[3]*s1[1]+s0[1]*s1[0]);
  mout[4] = scale * (s0[4]*s1[4]+s0[3]*s1[3]+s0[1]*s1[1]);
  mout[5] = scale * (s0[4]*s1[5]+s0[3]*s1[4]+s0[1]*s1[2]);
  mout[6] = scale * (s0[5]*s1[2]+s0[4]*s1[1]+s0[2]*s1[0]);
  mout[7] = scale * (s0[5]*s1[4]+s0[4]*s1[3]+s0[2]*s1[1]);
  mout[8] = scale * (s0[5]*s1[5]+s0[4]*s1[4]+s0[2]*s1[2]);
}

static inline void outerproduct3(const double* restrict v, double* restrict P)
{
  P[0] = v[0]*v[0];
  P[1] = v[0]*v[1];
  P[2] = v[0]*v[2];
  P[3] = v[1]*v[1];
  P[4] = v[1]*v[2];
  P[5] = v[2]*v[2];
}

static inline void outerproduct3_scaled(const double* restrict v, double* restrict P, double scale)
{
  P[0] = scale * v[0]*v[0];
  P[1] = scale * v[0]*v[1];
  P[2] = scale * v[0]*v[2];
  P[3] = scale * v[1]*v[1];
  P[4] = scale * v[1]*v[2];
  P[5] = scale * v[2]*v[2];
}

// conjugate 2 vectors (a, b) through a symmetric matrix S: a->transpose x S x b
// (%i2) sym3 : matrix([s0,s1,s2],
//                     [s1,s3,s4],
//                     [s2,s4,s5]);

// (%o2) matrix([s0,s1,s2],[s1,s3,s4],[s2,s4,s5])
// (%i6) a : matrix([a0],[a1],[a2]);

// (%o6) matrix([a0],[a1],[a2])
// (%i7) b : matrix([b0],[b1],[b2]);

// (%o7) matrix([b0],[b1],[b2])
// (%i10) transpose(a) . sym3 . b;

// (%o10) a2*(b2*s5+b1*s4+b0*s2)+a1*(b2*s4+b1*s3+b0*s1)+a0*(b2*s2+b1*s1+b0*s0)
static inline double conj_3(const double* restrict a, const double* restrict s, const double* restrict b)
{
  return a[2]*(b[2]*s[5]+b[1]*s[4]+b[0]*s[2])+a[1]*(b[2]*s[4]+b[1]*s[3]+b[0]*s[1])+a[0]*(b[2]*s[2]+b[1]*s[1]+b[0]*s[0]);
}


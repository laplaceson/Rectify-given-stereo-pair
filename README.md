# Rectify-given-stereo-pair
Using Microsoft Visual Studio 2013 + opencv3.0 

By arbitrarily selecting more than eight corresponding sample points on two pictures,
with the formula X'FX=0 ,using SVD or Least Square method to get Fundmental matrix F.
With both paired image,using I=FX to get the line after the projection, and do cross-
product on two line function to get epipole point of two plane.
Finally, use formula H=GST,G(Straighten the epipole line by project epipole point to infiniy)
R(Rotate) T(Transform), to get Homography matrix.

#Simple records of rectify image.
#You need to manually labeled more than eight points-pair.
#Unzip all the files andmore details information is in .word 
 

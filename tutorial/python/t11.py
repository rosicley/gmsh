# ------------------------------------------------------------------------------
#
#  Gmsh Python tutorial 11
#
#  Unstructured quadrangular meshes
#
# ------------------------------------------------------------------------------

import gmsh

model = gmsh.model
factory = model.geo

gmsh.initialize()
gmsh.option.setNumber("General.Terminal", 1)

gmsh.model.add("t11")

# We have seen in tutorials `t3.py' and `t6.py' that extruded and transfinite
# meshes can be "recombined" into quads, prisms or hexahedra. Unstructured
# meshes can be recombined in the same way. Let's define a simple geometry with
# an analytical mesh size field:

p1 = factory.addPoint(-1.25, -.5, 0)
p2 = factory.addPoint(1.25, -.5, 0)
p3 = factory.addPoint(1.25, 1.25, 0)
p4 = factory.addPoint(-1.25, 1.25, 0)

l1 = factory.addLine(p1, p2)
l2 = factory.addLine(p2, p3)
l3 = factory.addLine(p3, p4)
l4 = factory.addLine(p4, p1)

cl = factory.addCurveLoop([l1, l2, l3, l4])
pl = factory.addPlaneSurface([cl])

factory.synchronize()

field = model.mesh.field
field.add("MathEval", 1)
field.setString(1, "F", "0.01*(1.0+30.*(y-x*x)*(y-x*x) + (1-x)*(1-x))")
field.setAsBackgroundMesh(1)

# To generate quadrangles instead of triangles, we can simply add
model.mesh.setRecombine(2, pl)

# If we'd had several surfaces, we could have used the global option
# "Mesh.RecombineAll":
#
# gmsh.option.setNumber("Mesh.RecombineAll", 1)

# The default recombination algorithm is called "Blossom": it uses a minimum
# cost perfect matching algorithm to generate fully quadrilateral meshes from
# triangulations. More details about the algorithm can be found in the
# following paper: J.-F. Remacle, J. Lambrechts, B. Seny, E. Marchandise,
# A. Johnen and C. Geuzaine, "Blossom-Quad: a non-uniform quadrilateral mesh
# generator using a minimum cost perfect matching algorithm", International
# Journal for Numerical Methods in Engineering 89, pp. 1102-1119, 2012.

# For even better 2D (planar) quadrilateral meshes, you can try the
# experimental "Frontal-Delaunay for quads" meshing algorithm, which is a
# triangulation algorithm that enables to create right triangles almost
# everywhere: J.-F. Remacle, F. Henrotte, T. Carrier-Baudouin, E. Bechet,
# E. Marchandise, C. Geuzaine and T. Mouton. A frontal Delaunay quad mesh
# generator using the L^inf norm. International Journal for Numerical Methods
# in Engineering, 94, pp. 494-512, 2013. Uncomment the following line to try
# the Frontal-Delaunay algorithms for quads:
#
# gmsh.option.setNumber("Mesh.Algorithm", 8)

# The default recombination algorithm might leave some triangles in the mesh, if
# recombining all the triangles leads to badly shaped quads. In such cases, to
# generate full-quad meshes, you can either subdivide the resulting hybrid mesh
# (with `Mesh.SubdivisionAlgorithm' set to 1), or use the full-quad
# recombination algorithm, which will automatically perform a coarser mesh
# followed by recombination, smoothing and subdivision. Uncomment the following
# line to try the full-quad algorithm:
#
# gmsh.option.setNumber("Mesh.RecombinationAlgorithm", 2) # or 3

# You can also set the subdivision step alone, with
#
# gmsh.option.setNumber("Mesh.SubdivisionAlgorithm", 1)

model.mesh.generate(2)

# Note that you could also apply the recombination algorithm and/or the
# subdivision step explicitly after meshing, as follows:
#
# gmsh.model.mesh.generate(2)
# gmsh.model.mesh.recombine()
# gmsh.option.setNumber("Mesh.SubdivisionAlgorithm", 1)
# gmsh.model.mesh.refine()

# gmsh.fltk.run()

gmsh.finalize()
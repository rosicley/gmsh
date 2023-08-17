// merge a surface mesh (any format will work: .msh, .unv, etc.)

Merge "sphere-surf.stl";

// add a geometrical volume

Surface Loop(1) = {1};
Volume(1) = {1};

// use this to force a coarse mesh inside
Mesh.MeshSizeExtendFromBoundary = 0;
Mesh.MeshSizeMax = 0.5;

Mesh 3;
Mesh 2;

file1 = "spec.val";
Printf("No idea how to validate this yet :-(") >> file1;

xof 0303txt 0032

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame cube {
    FrameTransformMatrix {
      1000.000000, 0.000000, 0.000000, 0.000000,
       0.000000,100.000000, 0.000000, 0.000000,
       0.000000, 0.000000,100.000000, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
    }
    Mesh { // cube mesh
      24;
      -1.000000;-1.000000;-1.000000;,
      -1.000000;-1.000000; 1.000000;,
      -1.000000; 1.000000; 1.000000;,
      -1.000000; 1.000000;-1.000000;,
      -1.000000; 1.000000;-1.000000;,
      -1.000000; 1.000000; 1.000000;,
       1.000000; 1.000000; 1.000000;,
       1.000000; 1.000000;-1.000000;,
       1.000000; 1.000000;-1.000000;,
       1.000000; 1.000000; 1.000000;,
       1.000000;-1.000000; 1.000000;,
       1.000000;-1.000000;-1.000000;,
       1.000000;-1.000000;-1.000000;,
       1.000000;-1.000000; 1.000000;,
      -1.000000;-1.000000; 1.000000;,
      -1.000000;-1.000000;-1.000000;,
      -1.000000; 1.000000;-1.000000;,
       1.000000; 1.000000;-1.000000;,
       1.000000;-1.000000;-1.000000;,
      -1.000000;-1.000000;-1.000000;,
       1.000000; 1.000000; 1.000000;,
      -1.000000; 1.000000; 1.000000;,
      -1.000000;-1.000000; 1.000000;,
       1.000000;-1.000000; 1.000000;;
      6;
      4;3,2,1,0;,
      4;7,6,5,4;,
      4;11,10,9,8;,
      4;15,14,13,12;,
      4;19,18,17,16;,
      4;23,22,21,20;;
      MeshNormals { // cube normals
        6;
        -1.000000;-0.000000; 0.000000;,
         0.000000; 1.000000; 0.000000;,
         1.000000;-0.000000; 0.000000;,
         0.000000;-1.000000; 0.000000;,
         0.000000; 0.000000;-1.000000;,
         0.000000;-0.000000; 1.000000;;
        6;
        4;0,0,0,0;,
        4;1,1,1,1;,
        4;2,2,2,2;,
        4;3,3,3,3;,
        4;4,4,4,4;,
        4;5,5,5,5;;
      } // End of cube normals
      MeshTextureCoords { // cube UV coordinates
        24;
         0.999900; 0.000099;,
         0.000100; 0.000099;,
         0.000100; 0.999900;,
         0.999900; 0.999900;,
         0.000050; 0.250025;,
         0.000050; 0.499238;,
         0.997340; 0.499238;,
         0.997340; 0.250025;,
         0.000100; 0.999900;,
         0.999900; 0.999901;,
         0.999900; 0.000099;,
         0.000100; 0.000099;,
         0.997340; 0.999950;,
         0.997340; 0.749975;,
         0.000050; 0.749975;,
         0.000050; 0.999950;,
         0.000050; 0.250025;,
         0.997340; 0.250025;,
         0.997340; 0.000050;,
         0.000050; 0.000050;,
         0.997340; 0.499238;,
         0.000050; 0.499238;,
         0.000050; 0.749975;,
         0.997340; 0.749975;;
      } // End of cube UV coordinates
      MeshMaterialList { // cube material list
        1;
        6;
        0,
        0,
        0,
        0,
        0,
        0;
        Material mat {
           0.640000; 0.640000; 0.640000; 1.000000;;
           96.078431;
           0.500000; 0.500000; 0.500000;;
           0.000000; 0.000000; 0.000000;;
          TextureFilename {"Boxframe.png";}
        }
      } // End of cube material list
    } // End of cube mesh
  } // End of cube
} // End of Root

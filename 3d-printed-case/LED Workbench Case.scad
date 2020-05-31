$fa = 1;
$fs = 0.4;
//Box
//difference(){
//    union(){
//        cube([66,49,26]);
//        translate([0,-22,0])
//            cube([40,22,26]);
//    }
//    translate([2,2,2])
//        cube([62,45,24]);
//    translate([2,-20,2])
//        cube([36,22,24]);
//    rotate([270,0,0])
//        translate([12.5,-11.5,-22])
//            cylinder(h=2,r=2.5);
//    rotate([270,0,0])
//        translate([26,-11.5,-22])
//            cylinder(h=2,r=2.5);    
//
//
//}
//Lid
    union(){
        cube([66,49,2]);
        translate([0,-22,0])
            cube([40,22,2]);
    }
    translate([2,2,-2]){
        difference(){
            union(){
                cube([62,45,2]);
                translate([0,-22,0])
                    cube([36,20,2]);
            }
            translate([2,0,0]){
                cube([58,43,2]);
            }
            translate([2,-22,0])
                cube([32,20,2]);
        }
    }

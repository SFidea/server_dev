<?php

if (!empty($_GET)){
  $point_folder="/var/www/php/server_dev/data/stasm_points/";
  $o_image_folder="/var/www/php/server_dev/data/stasm_images/";
  $i_image_folder="/var/www/php/server_dev/data/upload_images/";
  $pt_name=$_GET["name"]. "_pt.txt";
  $o_img_name=$_GET["name"] . "_img.jpg";
  $stasm_folder="/var/www/php/server_dev/stasm/Debug/";
  $filename=$i_image_folder . $_GET["name"] . '.jpg';
  
  if (file_exists($filename)){
    $cmd=$stasm_folder ."stasm "  .$filename . " " . $point_folder . $pt_name . " " . $o_image_folder . $o_img_name ." " . $stasm_folder . "res/data/";

    $shell_output = shell_exec($cmd); //run stasm command from shell
    //echo "Res: " .$shell_output;
   
    if(file_exists($point_folder . $pt_name)){
      $json=file_get_contents($point_folder . $pt_name);
      $data=json_decode($json,TRUE);
      var_dump($data);
    }else{
      echo "The file " .$point_folder . $pt_name ." does not exist";
    }
         
	
  }else{
    echo "The file "  .$_GET["name"]. ".jpg does not exist";
  } 
 
}else{ //$_POST is empty
  echo "Perform code for page without POST data.";
}

?>

<?php

if (!empty($_GET)){
  $name=substr($_GET["name"],0,-4);
  $point_folder="/var/www/php/server_dev/data/stasm_points/";
  $o_image_folder="/var/www/php/server_dev/data/stasm_images/";
  $i_image_folder="/var/www/php/server_dev/data/upload_images/";
  $pt_name=$name. ".txt";
  $o_img_name=$name . ".jpg";
  $stasm_folder="/var/www/php/server_dev/stasm/Debug/";
  $filename=$i_image_folder . $name . '.jpg';
  
  if (file_exists($filename)){
    $cmd=$stasm_folder ."stasm "  .$filename . " " . $point_folder . $pt_name . " " . $o_image_folder . $o_img_name ." " . $stasm_folder . "res/data/";

    $shell_output = shell_exec($cmd); //run stasm command from shell
    //echo "Res: " .$shell_output;
   
    if(file_exists($point_folder . $pt_name)){
      $json=file_get_contents($point_folder . $pt_name);
      //$data=json_decode($json,TRUE);
      //var_dump($data);

      header('content-type: application/json');
      //echo (json_encode($json));
      echo $json;
    }else{
      echo "The file " .$point_folder . $pt_name ." does not exist";
    }
         
	
  }else{
    echo "The file "  .$name. ".jpg does not exist";
  } 
 
}else{ //$_POST is empty
  echo "Perform code for page without POST data.";
}

?>

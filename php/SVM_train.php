<?php

  $svm_folder="/home/user/Desktop/libsvm/libsvm/";
  $svm_model_folder="/home/user/Desktop/libsvm/libsvm/";
  $svm_data_folder="/home/user/Desktop/libsvm/libsvm/";
  
  //Used for simple test
  //$model_name="heart_scale.model";
  //$data_name="heart_scale";
  $model_name=$_GET["model_name"];
  $data_name=$_GET["data_name"];	

  if (file_exists($svm_data_folder.$data_name)){

    //TODO: add the parameter selection
    $para="";	
    $cmd= $svm_folder. 'svm-train ' .$para .$svm_data_folder.$data_name;
    //echo $cmd;
    $shell_output = shell_exec($cmd); //run stasm command from shell
    //echo "  Res: " .$shell_output;
 
  }else{
    echo "Training data/model does not exist";
  }
?>

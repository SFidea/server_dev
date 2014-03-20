<?php

  $svm_folder="/home/user/Desktop/libsvm/libsvm/";
  $svm_model_folder="/home/user/Desktop/libsvm/libsvm/";
  $svm_data_folder="/home/user/Desktop/libsvm/libsvm/";
  $svm_output_folder="/home/user/Desktop/libsvm/libsvm/";
  
  //Used for simple test
  //$model_name="heart_scale.model";
  //$output_name="output_file";
  //$data_name="heart_scale";
  $model_name=$_GET["model_name"];
  $output_name=$_GET["output_file"];
  $data_name=$_GET["data_name"];	

  
  if (file_exists($svm_model_folder.$model_name) 
      and file_exists($svm_data_folder.$data_name)){

    //TODO: add the probability output
    $cmd= $svm_folder. 'svm-predict ' .$svm_data_folder.$data_name .' '.$svm_model_folder.$model_name .' '. $svm_output_folder.$output_name;
    

    //$cmd= $svm_folder. 'svm-train -t 0 ' .$svm_data_folder.$data_name;
    //echo $cmd;
    $shell_output = shell_exec($cmd); //run stasm command from shell
 
    //echo "  Res: " .$shell_output;
   
    if(file_exists($svm_output_folder.$output_name)){
      $data=file_get_contents($svm_output_folder.$output_name);
      var_dump($data);
    }else{echo "Output file does not exist";}

  }else{
    echo "Training data/model does not exist";
  }
?>

<?php

function _cgproduct_page(){


  if (variable_get('enable_value', 0)) {

    $query = db_select('product', 'p')
    ->condition('p.pname', variable_get('title_value'), '=')
    ->fields('p', array('pid','pname', 'pcolor', 'pdescription', 'ptype'))
    ->range(0, 50);

    $var = '';
    $result = $query->execute();
    while($record = $result->fetchAssoc()) {

        $var .= 'Product:'.$record['pid'].'<br>' .'Name: '.$record['pname'].'<br>'.'Color: '.$record['pcolor'].'<br>'.'Description: '.$record['pdescription'].'<br>'.'Type: '.$record['ptype'].'<br>'.'<a href="/admin/cgproduct_update/'.$record['pid'].'">Edit</a>'.'<br>';
       //return $record['pname'].'<br>';

        //return 'aka';
        //'#markup' => 'Product Title:  ';
    }

    return $var;
  }
  else
  {
     return 'no content';
  }
}



// 	$form=array();

// 	$form['title'] = array(
//   		'#markup' => 'Product Title:  '.variable_get('title_value').'<br><br>',
// 	);

// 	$options = array(
//       1 => 'Red',
//       2 => 'Green',
//       3 => 'Blue',
//     );

// 	$form['color'] = array(
//   		'#markup' => 'Product Color: '.$options[variable_get('color_value')].'<br><br>',
// 	);
// 	$options_type = array(
//       1 => 'Toys',
//       2 => 'Tools',
//     );

// 	$form['type'] = array(
//   		'#markup' => 'Product type: '.$options_type[variable_get('type_value')].'<br><br>',
// 	);

// 	$form['description'] = array(
//   		'#markup' => 'Product Description:<br>'.variable_get('description_value').'<br><br>',
// 	);
//   if ($fid = variable_get('cgproduct_file', 0)) {
//     $file = file_load($fid);
//     $url = file_create_url($file->uri);
//     $form['image'] = array(
//       '#markup' => theme('image', array(
//         'path' => $url,
//         'title' => variable_get('title_value'),
//         'alt' => variable_get('description_value'),
//         'width' => '400px',
//         'height' => '',
//       )),
//     );
//   }



// 	return $form;
// }
// else
// {
// 	$form = array();
//   	$form['type'] = array(
//   		'#markup' => 'Product not displayed<br><br>',
// 	);
//   return $form;
// }
// }

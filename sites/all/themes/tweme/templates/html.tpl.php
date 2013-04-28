<?php

/**
 * @file
 * Custom theme implementation to display the basic html structure of a single
 * Drupal page.
 */

?>
<!DOCTYPE html>
<html lang="<?php print $language->language ?>">
<head profile="<?php print $grddl_profile ?>">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
	<?php print $head ?>
  <title><?php print $head_title ?></title>
  <?php print $styles ?>
  <?php print $scripts ?>
</head>
<body class="<?php print $classes ?>"<?php print $attributes ?>>
  <?php print $page_top ?>
  <?php print $page ?>
  <?php print $page_bottom ?>
</body>
</html>
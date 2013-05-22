<ul>
<?php foreach ($items as $item): ?>

  <li<?php if (isset($item['attributes'])) { print $this->attributes($item['attributes']); } ?>>
    <?php if (isset($item['link'])): ?><a href="<?php print $item['link']['href']; ?>"<?php if (isset($item['link']['attributes'])) { print $this->attributes($item['link']['attributes']); } ?>><?php endif; ?><?php print $item['content']; ?><?php if (isset($item['link'])): ?></a><?php endif; ?>

  </li>
<?php endforeach; ?>

</ul>
if ($args[0] -eq "-c") {
  $program = 'launcher.exe'
  $subsys = 'console'
} elseif ($args[0] -eq "-w") {
  $program = 'launcherw.exe'
  $subsys = 'windows'
} else {
  echo 'Need to specify -w (windows) or -c (console)'
  exit 1
}

if (-not (test-path $args[1])) {
  echo "Can't find file: $($args[1])"
  exit 1
}

$name = $args[1] -split '[/\\]'
$name = $name[$name.Length - 1]
cp $home\bin\$program $home\bin\$name
if (-not $?) {
  echo "Can't copy program to ~\bin\$name"
  exit 1
}
rcedit $home\bin\$name --set-resource-string 101 $args[1]
echo "made $subsys launcher ~\bin\$name --> $($args[1])"

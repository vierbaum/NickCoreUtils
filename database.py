#!/usr/bin/env python3

import os
import subprocess
str = "".join(["{}\\n".format(i) for i in os.listdir()])
lines = len(os.listdir()) if len(os.listdir()) < 20 else 20
os.system("echo -e '{}' | dmenu -l {}".format(str, lines))
print(subprocess.check_output(["echo", "-e '{}' | dmenu -l 10".format(str)]))

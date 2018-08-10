
### Runnind sudo commands in a shell script

The following steps will help you achieve the desired output:

    Create a new script file (replace create_dir.sh with your desired script name):

    vim ~/create_dir.sh

    The script will be created in the user’s home directory

    Add some commands that only a root or sudo user can execute like creating a folder at the root directory level:

    mkdir /abc

    Note: Don’t add sudo to these commands. Save and exit (using :wq!)

    Assign execute permissions to it using:

    sudo chmod u+x create_dir.sh

    Make changes so that this script doesn’t require a password.

        Open the sudoers file:

        sudo visudo -f /etc/sudoers

        Add the following line at the end:

        ahmad ALL=(root) NOPASSWD: /home/ahmad/create_dir.sh

        Replace ahmad with whatever your username is. Also make sure this is the last line. Save and exit.

    Now when running the command add sudo before it like:

    sudo ./create_dir.sh

    This will run the commands inside the script file without asking for a password.

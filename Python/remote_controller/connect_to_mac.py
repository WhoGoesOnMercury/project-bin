import paramiko
import os
from dotenv import load_dotenv

load_dotenv()

hostname = os.getenv("SSH_HOST")
port = int(os.getenv("SSH_PORT", 22))
username = os.getenv("SSH_USER")
password = os.getenv("SSH_PASS")

def ssh_shell():
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    
    try:
        ssh.connect(hostname, port=port, username=username, password=password)
        print(f"Connected to {hostname}. Type 'exit' to quit.")
        
        while True:
            command = input("mac> ").strip()
            if command.lower() in ("exit", "quit"):
                break

            stdin, stdout, stderr = ssh.exec_command(command)
            output = stdout.read().decode()
            errors = stderr.read().decode()

            if output:
                print(output, end="")
            if errors:
                print(f"[ERROR] {errors}", end="")

    except Exception as e:
        print(f"Connection failed: {e}")
    finally:
        ssh.close()
        
if __name__ == "__main__":
    ssh_shell()
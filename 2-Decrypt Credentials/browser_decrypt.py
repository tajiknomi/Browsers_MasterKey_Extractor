import sys
import os
import re
import sqlite3
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import padding

def validate_hex_key(secret_key):
    """
    Validates the format of the secret key (hex string).

    Args:
        secret_key (str): The secret key to validate.

    Returns:
        bool: True if the key is valid, False otherwise.
    """

    try:
        bytes.fromhex(secret_key)
        return True
    except ValueError:
        print("Invalid secret key format. Please enter a valid hex string.")
        return False


def decrypt_password(ciphertext, secret_key):
    """
    Decrypts a password using the AES-GCM algorithm.

    Args:
        ciphertext (bytes): The encrypted password.
        secret_key (bytes): The secret key used for decryption.

    Returns:
        str: The decrypted password (or an empty string on error).
    """

    try:
        initialisation_vector = ciphertext[3:15]
        encrypted_password = ciphertext[15:-16]
        tag = ciphertext[-16:]
        
        decryptor = Cipher(
            algorithms.AES(secret_key),
            modes.GCM(initialisation_vector, tag),
            backend=default_backend()
        ).decryptor()
        
        decrypted_pass = decryptor.update(encrypted_password) + decryptor.finalize()
        return decrypted_pass.decode()
    except Exception as e:
        print("[ERR] Unable to decrypt:", e)
        return ""


def get_db_connection(chrome_path_login_db):
    """
    Attempts to connect to the Chrome Login Data database.

    Args:
        chrome_path_login_db (str): The path to the Login Data database.

    Returns:
        sqlite3.Connection: The database connection object (or None on error).
    """

    try:
        print(chrome_path_login_db)
        conn = sqlite3.connect(chrome_path_login_db)
        return conn
    except sqlite3.Error as e:
        print("[ERR] SQLite database error:", e)
        return None
    except FileNotFoundError as e:
        print("[ERR] Chrome database not found:", e)
        return None


def main():
    
    if len(sys.argv) != 2:
        print("Usage: python script_name.py <path_to_login_data>")
        sys.exit(1)    

    # Get the path from the command-line argument
    chrome_path = sys.argv[1]

    # Trim trailing whitespace and quotes
    chrome_path = chrome_path.strip().strip('"').strip("'")

    # Normalize the path for consistent handling
    chrome_path = os.path.abspath(chrome_path)

    print(f"{chrome_path}\n\n")
    
    # Check if the path is a directory
    if os.path.isdir(chrome_path):
        # If it's a directory, search for the "Login Data" file in the directory
        chrome_path_login_db = os.path.join(chrome_path, "Login Data")
        if not os.path.isfile(chrome_path_login_db):
            print(f"'Login Data' file not found in the directory: {chrome_path}")
            sys.exit(1)
    elif os.path.isfile(chrome_path):
        # If it's a file, use the provided path
        chrome_path_login_db = chrome_path
    else: 
        print("The provided path is neither a file nor a directory.")
        sys.exit(1)

    secret_key = input("Input the Secret Key (Hex format)\n")
    while not validate_hex_key(secret_key):
        secret_key = input("Invalid format. Please re-enter secret key (Hex format):\n")
    secret_key = bytes.fromhex(secret_key)

    with get_db_connection(chrome_path_login_db) as conn:
        if conn:
            cursor = conn.cursor()
            cursor.execute("SELECT action_url, username_value, password_value FROM logins")
            for index, login in enumerate(cursor.fetchall()):
                url, username, ciphertext = login
                if url and username and ciphertext:
                    decrypted_password = decrypt_password(ciphertext, secret_key)
                    print(f"URL: {url}\nUser Name: {username}\nPassword: {decrypted_password}\n")
                    print("*" * 50)



if __name__ == "__main__":
    main()

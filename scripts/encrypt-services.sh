#!/bin/bash

set -e
BASE_DIR=$(pwd)

# NOTE: validate binary dependencies are installed
if ! command -v openssl &>/dev/null; then
  echo "Error: openssl is required but not installed. Please, refer to https://github.com/openssl/openssl" >&2
  exit 1
fi

if ! command -v yq &>/dev/null; then
  echo "Error: yq is required but not installed. Please, refer to https://github.com/mikefarah/yq" >&2
  exit 1
fi

password=""
salt=""
file=""
while [[ $# -gt 0 ]]; do
  case $1 in
    --password)
      password=$2
      shift 2
      ;;
    --salt)
      salt=$2
      shift 2
      ;;
	--file)
      file=$2
      shift 2
      ;;
    *)
      echo "Unknown option: $1"  >&2
      exit 1
      ;;
  esac
done


if [ -z "$file" ]; then
  echo "Error: The --file parameter is required. It must be a valid file path pointing to services.yml" >&2
  echo "Usage: $0 --file <file>" >&2
  echo "Example: $0 --file /Volumes/esp-sd/services.yml" >&2
  exit 1
fi

key=$(source $BASE_DIR/scripts/generate-key.sh --password "$password" --salt "$salt")

echo "Using key: $key to encrypt services.yml"

yq '.services[] | select(.secret != null) | .secret' "$file" | while IFS= read -r decrypted_secret; do
	echo "Processing secret: $decrypted_secret"
	encrypted_secret=$(echo "$decrypted_secret" | openssl enc -aes-256-ecb -e -K "$key" -base64 2>/dev/null)

	if [ $? -ne 0 ]; then
		echo "Error: Failed to encrypt secret: $decrypted_secret" >&2
		exit 1
	fi
	
	# NOTE: this ensures the encrypted secret is stored as a single line
	encrypted_secret=$(echo "$encrypted_secret" | tr -d "\n")
	echo "Encrypted secret: $encrypted_secret"

	yq -i "(.services[] | select(.secret == \"$decrypted_secret\") | .secret) = \"$encrypted_secret\"" "$file"
done


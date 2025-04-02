#!/bin/bash

# Base URL
BASE_URL="http://localhost:8080"

# Model to test
MODEL_NAME="llama2"  # ? change this if needed

echo "? Testing: GET /list (List all models)"
curl -s -X GET "$BASE_URL/list" | jq .
echo -e "\n? Done: /list\n"

echo "? Testing: GET /run/$MODEL_NAME (Run a model via GET)"
curl -s -X GET "$BASE_URL/run/$MODEL_NAME" | jq .
echo -e "\n? Done: /run/$MODEL_NAME\n"

echo "? Testing: POST /operation (Run a model via POST)"
curl -s -X POST "$BASE_URL/operation" \
  -H "Content-Type: application/json" \
  -d "{\"operation\": \"run_model\", \"model_to_run\": \"$MODEL_NAME\"}" | jq .
echo -e "\n? Done: /operation (run_model)\n"


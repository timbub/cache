#!/bin/bash
PROGRAM="../build/ideal"

TESTS_DIR="../tests"

echo "running E2E tests"
for INPUT_FILE in ${TESTS_DIR}/*.in; do

    BASENAME="${INPUT_FILE%.in}"

    EXPECTED_FILE="${BASENAME}.out"
    ACTUAL_FILE="${BASENAME}.act" # Используем .actual, чтобы не путать с другими файлами

${PROGRAM} < ${INPUT_FILE} > ${ACTUAL_FILE}

diff -q "${ACTUAL_FILE}" "${EXPECTED_FILE}"

if [ $? -eq 0 ]; then
    echo "TEST ${INPUT_FILE} PASSED"
else
    echo "TEST ${INPUT_FILE} FAILED"
    echo "--- Expected output: ---"
    cat "${EXPECTED_FILE}"
    echo "--- Actual output: ---"
    cat "${ACTUAL_FILE}"
    echo "------------------------"
fi

rm ${ACTUAL_FILE}
done

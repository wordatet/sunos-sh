#!/bin/bash
# Super Paranoid Stress Test 2.0 for SunOS 4.1.4 sh (AMD64)
# SunOS sh has native functions and 'unset'.

SH="./sh"
RECURSION_LIMIT=1500
CHURN_COUNT=50000
JOB_COUNT=200

echo "=== SunOS Super Paranoid Stress Suite 2.0 ==="

# 1. Stack Pressure (Native Functions)
echo "--- Test 1: Stack Exhaustion ($RECURSION_LIMIT levels) ---"
$SH << 'EOF'
r() {
    x=$1
    # Check modulo using expr
    m=`expr $x % 200`
    if test "$m" -eq 0; then
        echo "Depth $x..."
    fi
    if test "$x" != "1500"; then
        r `expr $x + 1`
    fi
}
echo "Starting native recursion (1500 levels)..."
r 1
EOF

if test $? -eq 0; then
    echo "PASS: Stack Recursion"
else
    echo "FAIL: Stack Recursion"
    exit 1
fi

# 2. Lightning Churn (50k variables)
echo "--- Test 2: Lightning Churn ($CHURN_COUNT variables) ---"
CHURN_SCRIPT="/tmp/churn_stress_sunos.sh"
echo "echo 'Generating churn script...'"
python3 -c "for i in range($CHURN_COUNT): print(f'V_{i}=val_{i}')" > "$CHURN_SCRIPT"
python3 -c "for i in range($CHURN_COUNT): print(f'unset V_{i}')" >> "$CHURN_SCRIPT"
echo "echo 'Churning memory...'" >> "$CHURN_SCRIPT"

$SH "$CHURN_SCRIPT" > /dev/null

if test $? -eq 0; then
    echo "PASS: Lightning Churn"
else
    echo "FAIL: Lightning Churn"
    rm -f "$CHURN_SCRIPT"
    exit 1
fi
rm -f "$CHURN_SCRIPT"

# 3. Command Substitution
echo "--- Test 3: Command Substitution ---"
RES=$($SH -c "echo \`echo bottom\`")
if test "$RES" = "bottom"; then
    echo "PASS: CmdSubst"
else
    echo "FAIL: CmdSubst (received: $RES)"
    exit 1
fi

# 4. Job Storm
echo "--- Test 4: Job Storm ($JOB_COUNT background procs) ---"
$SH << EOF
i=0
while test \$i -lt $JOB_COUNT; do
    (sleep 1) &
    i=\`expr \$i + 1\`
done
echo "Spawned $JOB_COUNT jobs. Waiting..."
wait
echo "Storm cleared."
EOF

if test $? -eq 0; then
    echo "PASS: Job Storm"
else
    echo "FAIL: Job Storm"
    exit 1
fi

echo "=== ALL SUNOS SUPER PARANOID TESTS PASSED ==="

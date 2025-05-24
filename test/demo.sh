#!/usr/bin/env bash
# Gruvbox Crisp Theme - Shell Script Demo
# Demonstrates various shell scripting syntax elements

# Shell options and error handling
set -euo pipefail
IFS=$'\n\t'

# Color definitions using ANSI escape codes
readonly RED='\033[0;31m'
readonly GREEN='\033[0;32m'
readonly YELLOW='\033[0;33m'
readonly BLUE='\033[0;34m'
readonly PURPLE='\033[0;35m'
readonly CYAN='\033[0;36m'
readonly RESET='\033[0m'

# Global variables
readonly SCRIPT_NAME="$(basename "${BASH_SOURCE[0]}")"
readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly VERSION="1.0.0"
readonly DEFAULT_CONFIG="${HOME}/.config/gruvbox/theme.conf"

# Configuration variables
THEME_NAME="${THEME_NAME:-gruvbox-crisp}"
DEBUG_MODE="${DEBUG:-false}"
VERBOSE="${VERBOSE:-0}"

# Function: Display usage information
usage() {
    cat << EOF
Usage: ${SCRIPT_NAME} [OPTIONS] COMMAND [ARGS]

A demonstration script for the Gruvbox Crisp theme.

COMMANDS:
    install     Install the theme
    uninstall   Remove the theme
    update      Update to the latest version
    config      Configure theme settings
    test        Run theme tests

OPTIONS:
    -h, --help              Show this help message
    -v, --version           Show version information
    -d, --debug             Enable debug mode
    -V, --verbose           Increase verbosity (can be used multiple times)
    -c, --config FILE       Use custom config file
    -t, --theme NAME        Specify theme name (default: ${THEME_NAME})

EXAMPLES:
    ${SCRIPT_NAME} install
    ${SCRIPT_NAME} --debug test
    ${SCRIPT_NAME} -c custom.conf config set contrast high

EOF
}

# Function: Logging utilities
log() {
    echo "[$(date +'%Y-%m-%d %H:%M:%S')] $*" >&2
}

log_info() {
    echo -e "${BLUE}[INFO]${RESET} $*" >&2
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${RESET} $*" >&2
}

log_warning() {
    echo -e "${YELLOW}[WARNING]${RESET} $*" >&2
}

log_error() {
    echo -e "${RED}[ERROR]${RESET} $*" >&2
}

log_debug() {
    if [[ "${DEBUG_MODE}" == "true" ]]; then
        echo -e "${PURPLE}[DEBUG]${RESET} $*" >&2
    fi
}

# Function: Error handling
die() {
    log_error "$1"
    exit "${2:-1}"
}

# Function: Check dependencies
check_dependencies() {
    local deps=("git" "curl" "jq")
    local missing=()
    
    for cmd in "${deps[@]}"; do
        if ! command -v "${cmd}" >/dev/null 2>&1; then
            missing+=("${cmd}")
        fi
    done
    
    if [[ ${#missing[@]} -gt 0 ]]; then
        die "Missing required dependencies: ${missing[*]}"
    fi
}

# Function: Parse command line arguments
parse_args() {
    local config_file=""
    
    while [[ $# -gt 0 ]]; do
        case "$1" in
            -h|--help)
                usage
                exit 0
                ;;
            -v|--version)
                echo "${SCRIPT_NAME} version ${VERSION}"
                exit 0
                ;;
            -d|--debug)
                DEBUG_MODE="true"
                shift
                ;;
            -V|--verbose)
                ((VERBOSE++))
                shift
                ;;
            -c|--config)
                config_file="$2"
                shift 2
                ;;
            -t|--theme)
                THEME_NAME="$2"
                shift 2
                ;;
            -*)
                die "Unknown option: $1" 1
                ;;
            *)
                break
                ;;
        esac
    done
    
    # Remaining arguments are the command and its args
    COMMAND="${1:-}"
    shift || true
    ARGS=("$@")
    
    # Validate config file if specified
    if [[ -n "${config_file}" ]]; then
        if [[ -f "${config_file}" ]]; then
            CONFIG_FILE="${config_file}"
        else
            die "Config file not found: ${config_file}"
        fi
    else
        CONFIG_FILE="${DEFAULT_CONFIG}"
    fi
}

# Function: Load configuration
load_config() {
    if [[ -f "${CONFIG_FILE}" ]]; then
        log_debug "Loading config from: ${CONFIG_FILE}"
        # shellcheck source=/dev/null
        source "${CONFIG_FILE}"
    else
        log_debug "Config file not found, using defaults"
    fi
}

# Function: Install theme
install_theme() {
    log_info "Installing ${THEME_NAME} theme..."
    
    # Create directories
    local theme_dir="${HOME}/.themes/${THEME_NAME}"
    mkdir -p "${theme_dir}"
    
    # Download theme files
    local repo_url="https://github.com/VatsalSy/zed-gruvbox_custom_themes"
    if command -v git >/dev/null 2>&1; then
        git clone --depth 1 "${repo_url}" "${theme_dir}" || die "Failed to clone repository"
    else
        curl -L "${repo_url}/archive/main.tar.gz" | tar -xz -C "${theme_dir}" --strip-components=1
    fi
    
    # Run post-install hooks
    if [[ -x "${theme_dir}/install.sh" ]]; then
        log_debug "Running post-install script"
        "${theme_dir}/install.sh"
    fi
    
    log_success "Theme installed successfully!"
}

# Function: Test theme
test_theme() {
    log_info "Running theme tests..."
    
    # Array manipulation
    local -a test_files=(
        "test_syntax.sh"
        "test_colors.sh"
        "test_contrast.sh"
    )
    
    # Associative array
    declare -A test_results
    
    # Run tests
    for test_file in "${test_files[@]}"; do
        if [[ -f "${SCRIPT_DIR}/${test_file}" ]]; then
            log_debug "Running ${test_file}"
            if bash "${SCRIPT_DIR}/${test_file}"; then
                test_results["${test_file}"]="PASS"
            else
                test_results["${test_file}"]="FAIL"
            fi
        fi
    done
    
    # Display results
    echo "Test Results:"
    for test in "${!test_results[@]}"; do
        if [[ "${test_results[$test]}" == "PASS" ]]; then
            echo -e "  ${GREEN}✓${RESET} ${test}"
        else
            echo -e "  ${RED}✗${RESET} ${test}"
        fi
    done
}

# Function: Configure theme
configure_theme() {
    local action="${ARGS[0]:-}"
    local key="${ARGS[1]:-}"
    local value="${ARGS[2]:-}"
    
    case "${action}" in
        get)
            if [[ -n "${key}" ]]; then
                grep "^${key}=" "${CONFIG_FILE}" | cut -d'=' -f2-
            else
                cat "${CONFIG_FILE}"
            fi
            ;;
        set)
            [[ -z "${key}" ]] && die "Key required for set operation"
            [[ -z "${value}" ]] && die "Value required for set operation"
            
            # Create config file if it doesn't exist
            mkdir -p "$(dirname "${CONFIG_FILE}")"
            touch "${CONFIG_FILE}"
            
            # Update or add the key-value pair
            if grep -q "^${key}=" "${CONFIG_FILE}"; then
                sed -i.bak "s/^${key}=.*/${key}=${value}/" "${CONFIG_FILE}"
            else
                echo "${key}=${value}" >> "${CONFIG_FILE}"
            fi
            
            log_success "Configuration updated: ${key}=${value}"
            ;;
        *)
            die "Unknown config action: ${action}"
            ;;
    esac
}

# Function: Process management example
background_task() {
    local pid_file="/tmp/${SCRIPT_NAME}.pid"
    
    # Start background process
    {
        echo $$ > "${pid_file}"
        while true; do
            log_debug "Background task running..."
            sleep 10
        done
    } &
    
    local bg_pid=$!
    log_info "Started background task with PID: ${bg_pid}"
    
    # Trap signals
    trap 'kill ${bg_pid} 2>/dev/null; rm -f ${pid_file}' EXIT INT TERM
    
    # Wait for process
    wait ${bg_pid}
}

# Function: Advanced string manipulation
process_string() {
    local input="$1"
    
    # String length
    echo "Length: ${#input}"
    
    # Substring extraction
    echo "First 5 chars: ${input:0:5}"
    echo "Last 5 chars: ${input: -5}"
    
    # String replacement
    echo "Replace 'theme': ${input//theme/THEME}"
    
    # Case conversion
    echo "Uppercase: ${input^^}"
    echo "Lowercase: ${input,,}"
    
    # Pattern matching
    if [[ "${input}" =~ ^[Gg]ruvbox.*theme$ ]]; then
        echo "String matches Gruvbox theme pattern"
    fi
}

# Function: File operations
process_files() {
    local search_dir="${1:-.}"
    
    # Find all theme files
    while IFS= read -r -d '' file; do
        log_debug "Processing: ${file}"
        
        # Get file info
        local size
        size=$(stat -f%z "${file}" 2>/dev/null || stat -c%s "${file}")
        local modified
        modified=$(stat -f%m "${file}" 2>/dev/null || stat -c%Y "${file}")
        
        echo "File: ${file}, Size: ${size} bytes, Modified: $(date -r "${modified}" 2>/dev/null || date -d "@${modified}")"
    done < <(find "${search_dir}" -name "*.theme" -type f -print0)
}

# Function: Here documents and process substitution
generate_config() {
    cat << 'CONFIG'
# Gruvbox Crisp Theme Configuration
# Generated on: $(date)

[theme]
name = gruvbox-crisp
version = 1.0.0
author = Vatsal Sanjay

[colors]
background = #1d2021
foreground = #ebdbb2
red = #fb4934
green = #b8bb26
yellow = #fabd2f
blue = #83a598
purple = #d3869b
aqua = #8ec07c
orange = #fe8019

[settings]
high_contrast = true
italic_comments = true
bold_keywords = true
CONFIG
}

# Function: Complex conditionals
check_environment() {
    # Check OS
    case "$(uname -s)" in
        Linux*)
            OS="Linux"
            if [[ -f /etc/os-release ]]; then
                # shellcheck source=/dev/null
                source /etc/os-release
                DISTRO="${NAME}"
            fi
            ;;
        Darwin*)
            OS="macOS"
            DISTRO="$(sw_vers -productName) $(sw_vers -productVersion)"
            ;;
        CYGWIN*|MINGW*|MSYS*)
            OS="Windows"
            DISTRO="Windows (Unix-like environment)"
            ;;
        *)
            OS="Unknown"
            DISTRO="Unknown"
            ;;
    esac
    
    log_info "Operating System: ${OS}"
    log_info "Distribution: ${DISTRO}"
}

# Function: Mathematical operations
calculate() {
    local -i a=42
    local -i b=7
    
    echo "Arithmetic operations:"
    echo "  $a + $b = $((a + b))"
    echo "  $a - $b = $((a - b))"
    echo "  $a * $b = $((a * b))"
    echo "  $a / $b = $((a / b))"
    echo "  $a % $b = $((a % b))"
    echo "  $a ** 2 = $((a ** 2))"
    
    # Bitwise operations
    echo "Bitwise operations:"
    echo "  $a & $b = $((a & b))"
    echo "  $a | $b = $((a | b))"
    echo "  $a ^ $b = $((a ^ b))"
    echo "  ~$a = $((~a))"
    echo "  $a << 2 = $((a << 2))"
    echo "  $a >> 2 = $((a >> 2))"
}

# Main function
main() {
    # Parse arguments
    parse_args "$@"
    
    # Check dependencies
    check_dependencies
    
    # Load configuration
    load_config
    
    # Execute command
    case "${COMMAND}" in
        install)
            install_theme
            ;;
        uninstall)
            log_warning "Uninstall not implemented yet"
            ;;
        update)
            log_warning "Update not implemented yet"
            ;;
        config)
            configure_theme
            ;;
        test)
            test_theme
            ;;
        *)
            if [[ -z "${COMMAND}" ]]; then
                usage
                exit 1
            else
                die "Unknown command: ${COMMAND}"
            fi
            ;;
    esac
}

# Script execution guard
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    main "$@"
fi
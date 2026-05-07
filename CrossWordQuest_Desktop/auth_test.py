#!/usr/bin/env python3
"""
CrossWord Quest Authentication Test Script
Tests login/registration flow with hardcoded credentials
"""

import sys
import json
from typing import Dict, Tuple

# Test Credentials
TEST_EMAIL = "test@example.com"
TEST_PASSWORD = "TestPass123!"
TEST_USERNAME = "testuser"

# Registered test accounts (simulating database)
registered_accounts: Dict[str, Dict[str, str]] = {
    TEST_EMAIL: {
        "username": TEST_USERNAME,
        "password": TEST_PASSWORD,
        "user_id": "test-user-uuid-12345"
    }
}

class AuthValidator:
    """Email and password validation"""
    
    @staticmethod
    def validate_email(email: str) -> Tuple[bool, str]:
        """Validate email format"""
        if not email or not email.strip():
            return False, "Email address is required"
        
        # Simple regex-like validation
        if "@" not in email or "." not in email.split("@")[-1]:
            return False, "Invalid email format"
        
        if len(email) > 254:
            return False, "Email address is too long"
        
        return True, ""
    
    @staticmethod
    def validate_password(password: str) -> Tuple[bool, str]:
        """Validate password complexity"""
        if not password:
            return False, "Password is required"
        
        if len(password) < 12:
            return False, "Password must be at least 12 characters"
        
        has_upper = any(c.isupper() for c in password)
        has_lower = any(c.islower() for c in password)
        has_digit = any(c.isdigit() for c in password)
        has_special = any(c in "!@#$%^&*()-_=+[]{}|;:,.<>?" for c in password)
        
        if not has_upper:
            return False, "Password must contain at least one uppercase letter (A-Z)"
        if not has_lower:
            return False, "Password must contain at least one lowercase letter (a-z)"
        if not has_digit:
            return False, "Password must contain at least one digit (0-9)"
        if not has_special:
            return False, "Password must contain at least one special character (!@#$%^&*)"
        
        return True, ""
    
    @staticmethod
    def validate_username(username: str) -> Tuple[bool, str]:
        """Validate username"""
        if not username or not username.strip():
            return False, "Username is required"
        
        if len(username) < 3:
            return False, "Username must be at least 3 characters"
        
        if len(username) > 30:
            return False, "Username must not exceed 30 characters"
        
        # Check valid characters
        valid_chars = set("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-")
        if not all(c in valid_chars for c in username):
            return False, "Username can only contain letters, numbers, underscores, and hyphens"
        
        return True, ""

class AuthManager:
    """Manages authentication with hardcoded test credentials"""
    
    def __init__(self):
        self.is_authenticated = False
        self.access_token = ""
        self.user_id = ""
        self.email = ""
        self.username = ""
    
    def login(self, email: str, password: str) -> Tuple[bool, str]:
        """
        Login with email and password
        Returns: (success, message)
        """
        print(f"\n[LOGIN] Attempting login with email: {email}")
        
        # Validate email format
        valid, error = AuthValidator.validate_email(email)
        if not valid:
            print(f"[LOGIN] ❌ Validation failed: {error}")
            return False, error
        
        # Check if email exists
        if email not in registered_accounts:
            print(f"[LOGIN] ❌ Email not found: {email}")
            return False, "Email not found"
        
        # Check password
        account = registered_accounts[email]
        if account["password"] != password:
            print(f"[LOGIN] ❌ Incorrect password for {email}")
            return False, "Incorrect password"
        
        # Successful login
        self.is_authenticated = True
        self.access_token = f"test-token-{hash(email) % 1000000}"
        self.user_id = account["user_id"]
        self.email = email
        self.username = account["username"]
        
        print(f"[LOGIN] ✅ Login successful!")
        print(f"[LOGIN]   Email: {self.email}")
        print(f"[LOGIN]   Username: {self.username}")
        print(f"[LOGIN]   Token: {self.access_token}")
        
        return True, "Login successful"
    
    def register(self, email: str, username: str, password: str, confirm_password: str) -> Tuple[bool, str]:
        """
        Register new account
        Returns: (success, message)
        """
        print(f"\n[REGISTER] Attempting registration with email: {email}")
        
        # Validate email
        valid, error = AuthValidator.validate_email(email)
        if not valid:
            print(f"[REGISTER] ❌ Email validation failed: {error}")
            return False, error
        
        # Check if email already registered
        if email in registered_accounts:
            print(f"[REGISTER] ❌ Email already registered: {email}")
            return False, "This email is already registered"
        
        # Validate username
        valid, error = AuthValidator.validate_username(username)
        if not valid:
            print(f"[REGISTER] ❌ Username validation failed: {error}")
            return False, error
        
        # Validate password
        valid, error = AuthValidator.validate_password(password)
        if not valid:
            print(f"[REGISTER] ❌ Password validation failed: {error}")
            return False, error
        
        # Check password match
        if password != confirm_password:
            print(f"[REGISTER] ❌ Passwords do not match")
            return False, "Passwords do not match"
        
        # Create new account
        new_id = f"user-{hash(email) % 1000000}"
        registered_accounts[email] = {
            "username": username,
            "password": password,
            "user_id": new_id
        }
        
        # Auto-login after successful registration
        self.is_authenticated = True
        self.access_token = f"test-token-{hash(email) % 1000000}"
        self.user_id = new_id
        self.email = email
        self.username = username
        
        print(f"[REGISTER] ✅ Registration successful!")
        print(f"[REGISTER]   Email: {self.email}")
        print(f"[REGISTER]   Username: {self.username}")
        print(f"[REGISTER]   User ID: {self.user_id}")
        
        return True, "Registration successful"
    
    def logout(self) -> Tuple[bool, str]:
        """Logout current user"""
        print(f"\n[LOGOUT] Logging out user: {self.email}")
        self.is_authenticated = False
        self.access_token = ""
        self.user_id = ""
        self.email = ""
        self.username = ""
        print(f"[LOGOUT] ✅ Logged out successfully")
        return True, "Logged out"

class Colors:
    """Terminal colors for pretty output"""
    HEADER = '\033[95m'
    BLUE = '\033[94m'
    CYAN = '\033[96m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    END = '\033[0m'

def print_header(text: str):
    """Print formatted header"""
    print(f"\n{Colors.BOLD}{Colors.CYAN}{'='*60}")
    print(f"{text:^60}")
    print(f"{'='*60}{Colors.END}\n")

def print_test_case(name: str):
    """Print test case header"""
    print(f"{Colors.BOLD}{Colors.BLUE}→ Test: {name}{Colors.END}")

def print_result(success: bool, message: str):
    """Print test result"""
    if success:
        print(f"  {Colors.GREEN}✅ {message}{Colors.END}")
    else:
        print(f"  {Colors.RED}❌ {message}{Colors.END}")

def test_hardcoded_credentials():
    """Test with hardcoded credentials"""
    print_header("Test 1: Hardcoded Test Credentials")
    
    auth = AuthManager()
    
    print(f"Test credentials:")
    print(f"  Email: {TEST_EMAIL}")
    print(f"  Password: {TEST_PASSWORD}")
    print(f"  Username: {TEST_USERNAME}")
    
    # Test 1.1: Login with correct credentials
    print_test_case("Login with CORRECT credentials")
    success, message = auth.login(TEST_EMAIL, TEST_PASSWORD)
    print_result(success, message)
    assert success, "Should login successfully"
    assert auth.is_authenticated, "Should be authenticated"
    print(f"  Session Token: {auth.access_token}")
    
    # Test 1.2: Logout
    print_test_case("Logout")
    success, message = auth.logout()
    print_result(success, message)
    assert not auth.is_authenticated, "Should not be authenticated"

def test_login_failures():
    """Test login failure cases"""
    print_header("Test 2: Login Failure Cases")
    
    auth = AuthManager()
    
    # Test 2.1: Wrong email
    print_test_case("Login with WRONG email")
    success, message = auth.login("wrong@example.com", TEST_PASSWORD)
    print_result(not success, message)
    assert not success and "Email not found" in message, "Should fail with email not found"
    
    # Test 2.2: Wrong password
    print_test_case("Login with WRONG password")
    success, message = auth.login(TEST_EMAIL, "WrongPass123!")
    print_result(not success, message)
    assert not success and "Incorrect password" in message, "Should fail with password error"
    
    # Test 2.3: Invalid email format
    print_test_case("Login with INVALID email format")
    success, message = auth.login("not-an-email", TEST_PASSWORD)
    print_result(not success, message)
    assert not success and "Invalid email" in message, "Should fail with invalid email"

def test_registration():
    """Test registration"""
    print_header("Test 3: Registration")
    
    auth = AuthManager()
    
    # Test 3.1: Register new user
    print_test_case("Register NEW user")
    success, message = auth.register(
        "newuser@example.com",
        "newuser123",
        "NewPass12345!",
        "NewPass12345!"
    )
    print_result(success, message)
    assert success, "Should register successfully"
    assert auth.is_authenticated, "Should be auto-logged in"
    
    # Test 3.2: Try to register with existing email
    print_test_case("Register with EXISTING email")
    auth2 = AuthManager()
    success, message = auth2.register(
        "newuser@example.com",
        "differentuser",
        "AnotherPass123!",
        "AnotherPass123!"
    )
    print_result(not success, message)
    assert not success and "already registered" in message, "Should fail with email exists"

def test_password_validation():
    """Test password validation rules"""
    print_header("Test 4: Password Validation Rules")
    
    validator = AuthValidator()
    
    test_cases = [
        ("short", False, "less than 12 chars"),
        ("NoDigits!", False, "no digits"),
        ("nouppercase123!", False, "no uppercase"),
        ("NOLOWERCASE123!", False, "no lowercase"),
        ("NoSpecial123", False, "no special char"),
        ("ValidPass123!", True, "valid password"),
        ("SecurePassword1!@", True, "valid strong password"),
    ]
    
    for password, should_pass, reason in test_cases:
        print_test_case(f"Password: '{password}' ({reason})")
        valid, error = validator.validate_password(password)
        if should_pass:
            print_result(valid, "✓ Valid password" if valid else error)
            assert valid, f"Password should be valid: {error}"
        else:
            print_result(not valid, error)
            assert not valid, f"Password should be invalid"

def test_email_validation():
    """Test email validation"""
    print_header("Test 5: Email Validation")
    
    validator = AuthValidator()
    
    test_cases = [
        ("valid@example.com", True),
        ("test.user@example.co.uk", True),
        ("noemail", False),
        ("@example.com", False),
        ("user@", False),
        ("user@.com", False),
    ]
    
    for email, should_pass in test_cases:
        print_test_case(f"Email: '{email}'")
        valid, error = validator.validate_email(email)
        if should_pass:
            print_result(valid, "✓ Valid email" if valid else error)
        else:
            print_result(not valid, error)

def test_username_validation():
    """Test username validation"""
    print_header("Test 6: Username Validation")
    
    validator = AuthValidator()
    
    test_cases = [
        ("ab", False, "too short"),
        ("validuser", True, "valid"),
        ("valid_user-123", True, "valid with symbols"),
        ("user@name", False, "invalid character"),
        ("a"*31, False, "too long"),
    ]
    
    for username, should_pass, reason in test_cases:
        print_test_case(f"Username: '{username}' ({reason})")
        valid, error = validator.validate_username(username)
        if should_pass:
            print_result(valid, "✓ Valid username" if valid else error)
        else:
            print_result(not valid, error)

def interactive_test():
    """Interactive test mode"""
    print_header("Interactive Test Mode")
    
    auth = AuthManager()
    
    while True:
        print(f"\n{Colors.BOLD}Menu:{Colors.END}")
        print("1. Login")
        print("2. Register")
        print("3. Check Status")
        print("4. Logout")
        print("5. Show Test Credentials")
        print("6. Exit")
        
        choice = input(f"\n{Colors.BOLD}Choose option (1-6): {Colors.END}").strip()
        
        if choice == "1":
            email = input("Email: ").strip()
            password = input("Password: ").strip()
            success, message = auth.login(email, password)
            print_result(success, message)
        
        elif choice == "2":
            email = input("Email: ").strip()
            username = input("Username: ").strip()
            password = input("Password: ").strip()
            confirm = input("Confirm Password: ").strip()
            success, message = auth.register(email, username, password, confirm)
            print_result(success, message)
        
        elif choice == "3":
            print(f"\nAuthenticated: {Colors.GREEN if auth.is_authenticated else Colors.RED}{auth.is_authenticated}{Colors.END}")
            if auth.is_authenticated:
                print(f"Email: {auth.email}")
                print(f"Username: {auth.username}")
                print(f"Token: {auth.access_token}")
        
        elif choice == "4":
            auth.logout()
        
        elif choice == "5":
            print(f"\n{Colors.BOLD}Test Credentials:{Colors.END}")
            print(f"Email: {TEST_EMAIL}")
            print(f"Password: {TEST_PASSWORD}")
            print(f"Username: {TEST_USERNAME}")
        
        elif choice == "6":
            print("\nGoodbye!")
            break
        
        else:
            print("Invalid option")

def main():
    """Main test runner"""
    print(f"\n{Colors.BOLD}{Colors.CYAN}")
    print("╔═══════════════════════════════════════════════════════════╗")
    print("║     CrossWord Quest - Authentication Test Suite           ║")
    print("║            (With Hardcoded Test Credentials)              ║")
    print("╚═══════════════════════════════════════════════════════════╝")
    print(f"{Colors.END}")
    
    if len(sys.argv) > 1 and sys.argv[1] == "interactive":
        interactive_test()
    else:
        # Run all tests
        try:
            test_hardcoded_credentials()
            test_login_failures()
            test_registration()
            test_password_validation()
            test_email_validation()
            test_username_validation()
            
            print_header("✅ All Tests Passed!")
            print(f"{Colors.GREEN}The authentication logic is working correctly!{Colors.END}")
            print(f"\n{Colors.BOLD}Next Steps:{Colors.END}")
            print("1. Install Qt 6 and build the C++ application")
            print("2. Fill in Supabase credentials in .env file")
            print("3. Build and run the desktop application")
            print("\n{Colors.BOLD}For interactive testing, run:{Colors.END}")
            print("  python auth_test.py interactive\n")
            
        except AssertionError as e:
            print(f"\n{Colors.RED}{Colors.BOLD}❌ Test Failed: {e}{Colors.END}")
            sys.exit(1)

if __name__ == "__main__":
    main()

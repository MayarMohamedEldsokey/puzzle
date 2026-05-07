# CrossWord Quest Desktop - Authentication UI

A C++ Qt6 desktop application for game authentication with Supabase backend integration.

## Features

✅ **Login Screen** - Authenticate existing users with email/password
✅ **Registration Screen** - Create new accounts with email/password validation
✅ **Password Strength Validation** - 12+ characters with uppercase, lowercase, numbers, and special characters
✅ **Email Validation** - Client-side email format checking
✅ **Error Handling** - Specific error messages (email not found vs wrong password)
✅ **Supabase Integration** - REST API authentication with JWT tokens
✅ **Single-Session Authentication** - Tokens stored in memory (cleared on app exit)

## Project Structure

```
CrossWordQuest_Desktop/
├── CMakeLists.txt                 # Qt/CMake build configuration
├── .env.example                   # Supabase credentials template
├── README.md
│
├── src/
│   ├── main.cpp                   # Application entry point
│   ├── mainwindow.h/cpp           # Main window & screen navigation
│   │
│   ├── auth/                      # Authentication layer
│   │   ├── supabase_client.h/cpp  # Supabase REST API wrapper
│   │   ├── auth_manager.h/cpp     # Auth session manager
│   │   ├── validators.h/cpp       # Email/password validation
│   │   └── error_handler.h/cpp    # Error message mapping
│   │
│   ├── ui/                        # UI Components
│   │   ├── login_screen.h/cpp     # Login screen widget
│   │   └── registration_screen.h/cpp # Registration screen widget
│   │
│   └── models/
│       └── user_model.h/cpp       # User data model
│
└── resources/
    └── resources.qrc              # Qt resource file
```

## Requirements

- **Qt 6.x** (Core, Gui, Widgets, Network)
- **CMake 3.21+**
- **C++17 compiler** (MSVC 2019+, GCC 9+, Clang 10+)
- **Supabase project** with authentication enabled

## Setup

### 1. Install Qt6

**Windows:**
- Download Qt Online Installer from https://www.qt.io/download-open-source
- Install Qt 6.x with MSVC compiler

**macOS/Linux:**
```bash
# macOS (using Homebrew)
brew install qt@6

# Linux (Ubuntu/Debian)
sudo apt-get install qt6-base-dev qt6-tools-dev
```

### 2. Configure Supabase Credentials

1. Copy `.env.example` to `.env`
2. Fill in your Supabase credentials:

```bash
cp .env.example .env
```

Edit `.env`:
```
SUPABASE_URL=https://your-project.supabase.co
SUPABASE_ANON_KEY=your-public-anon-key
```

Get these from:
- Go to https://app.supabase.com
- Select your project
- Settings → API → Project URL and anon key

### 3. Build Project

**Using CMake (Recommended):**

```bash
# Create build directory
mkdir build && cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build .

# Run
./bin/CrossWordQuestAuth
```

**Using Qt Creator:**

1. Open `CMakeLists.txt` in Qt Creator
2. Select "Desktop (MSVC 2022)" or your compiler
3. Click Build → Build All
4. Click Run

## Features Details

### Password Validation Rules

✅ Minimum 12 characters
✅ At least 1 uppercase letter (A-Z)
✅ At least 1 lowercase letter (a-z)
✅ At least 1 digit (0-9)
✅ At least 1 special character (!@#$%^&*)

### Email Validation

Regex pattern: `^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$`

### Authentication Flow

```
User Input → Client Validation → Supabase REST API → JWT Token Response
                                        ↓
                            Error Mapping to User-Friendly Message
```

### Error Handling

| Status | Error | Message |
|--------|-------|---------|
| 400 | Invalid credentials | "Invalid email or password" |
| 400 | User already exists | "This email is already registered" |
| 401 | Wrong password | "Incorrect password" |
| 404 | Email not found | "Email not found" |
| 422 | Validation failed | "Invalid request" |
| 5xx | Server error | "Server error. Please try again later." |

## Authentication API Endpoints

### Sign Up
```
POST /auth/v1/signup
Body: {
  "email": "user@example.com",
  "password": "SecurePass123!",
  "user_metadata": { "username": "john_doe" }
}
```

### Sign In
```
POST /auth/v1/token?grant_type=password
Body: {
  "email": "user@example.com",
  "password": "SecurePass123!"
}
```

Response:
```json
{
  "access_token": "jwt_token_here",
  "refresh_token": "refresh_token",
  "user": {
    "id": "user-uuid",
    "email": "user@example.com"
  }
}
```

## Session Management

- **Token Storage**: In-memory only (single-session)
- **Token Expiry**: Handled by Supabase (typically 3600 seconds)
- **Session Persistence**: None (cleared on app exit)

## Build Options

### Release Build (Optimized)
```bash
mkdir build-release && cd build-release
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### Debug Build (Debugging symbols)
```bash
mkdir build-debug && cd build-debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
```

## Testing

### Manual Testing Checklist

- [ ] **Login Success**: Correct email/password → success message
- [ ] **Login Failure - Wrong Email**: Show "Email not found"
- [ ] **Login Failure - Wrong Password**: Show "Incorrect password"
- [ ] **Registration - Valid Data**: Successfully create account
- [ ] **Registration - Email Already Exists**: Show appropriate error
- [ ] **Registration - Weak Password**: Show each failed requirement
- [ ] **Password Strength Indicator**: Updates in real-time
- [ ] **Form Validation**: Errors clear when user types
- [ ] **Session**: Closes cleanly when app exits

## Common Issues

### Build Error: "Qt6 not found"
```bash
# Set Qt path
cmake .. -DCMAKE_PREFIX_PATH=/path/to/qt6 -DCMAKE_BUILD_TYPE=Release
```

### Network Error at Runtime
- Check `.env` file exists in build directory
- Verify Supabase URL and key are correct
- Ensure internet connection is active

### SSL Certificate Error
- Update system certificates
- On Windows: Download latest root certificates
- On macOS: Run "Install Certificates.command" from Python installation

## Next Steps

To extend this application:

1. **Add Dashboard Screen** - Show user profile and game list after login
2. **Implement Forgot Password** - Add password reset flow
3. **Add Social Auth** - Integrate Steam/Google OAuth
4. **Persistent Sessions** - Store tokens securely (encryption required)
5. **Offline Mode** - Cache authentication locally

## Dependencies

- **Qt 6** - GUI framework
- **QNetworkAccessManager** - HTTPS requests
- **QJsonDocument** - JSON parsing
- **nlohmann/json** - (Optional) Advanced JSON handling

All dependencies are included with Qt6 or are header-only libraries.

## License

This project is provided as-is for educational purposes.

## Support

For issues:
1. Check the error message carefully - it's specific
2. Verify `.env` configuration
3. Check Supabase project settings
4. Review build output for compilation errors
5. Enable debug mode: `cmake .. -DCMAKE_BUILD_TYPE=Debug`

## Security Notes

⚠️ **Important Security Reminders**

- Never commit `.env` file with real credentials to version control
- Always use HTTPS for all API calls (Qt handles this by default)
- Never log sensitive data (passwords, tokens)
- Use Supabase RLS policies to secure database tables
- Consider SSL certificate pinning for production

## Architecture Decisions

### Why REST API over Direct Database Connection?
- Client security: Database credentials never exposed
- Supabase handles authentication and authorization
- Stateless, easier to scale

### Why Single-Session?
- Simpler implementation for desktop app
- Better security for shared machines
- User explicitly logs in each session

### Why Specific Error Messages?
- Better UX: Users know what went wrong
- Acceptable security trade-off for desktop apps
- Standard practice in desktop applications

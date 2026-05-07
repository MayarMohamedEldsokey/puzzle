# Supabase Setup Guide

## Create Supabase Project

1. Go to https://app.supabase.com
2. Click "New project"
3. Fill in project details:
   - **Name**: CrossWord Quest Auth
   - **Database Password**: (strong password, save it)
   - **Region**: Choose closest to you
4. Click "Create new project"
5. Wait for project to initialize (2-3 minutes)

## Get API Credentials

1. In Supabase dashboard, go to **Settings** → **API**
2. Copy:
   - **Project URL**: `https://your-project.supabase.co`
   - **anon public key**: Your anonymous public API key
   - **service_role secret**: (keep private, server-side only)

3. Paste into `.env` file:
   ```
   SUPABASE_URL=https://your-project.supabase.co
   SUPABASE_ANON_KEY=your_public_anon_key_here
   ```

## Enable Authentication

1. In Supabase dashboard, go to **Authentication**
2. Click **Providers**
3. Enable **Email** (default enabled)
4. Go to **Settings** → **Email Templates**
5. You can customize confirmation emails (optional)

## Configure Email Auth

### For Local Testing:
1. Go to **Authentication** → **Settings**
2. Under **Email confirm status**, select:
   - "Confirm email" (recommended for production)
   - "Auto confirm email" (testing only, auto-confirms new users)
3. Set email rate limit (default: 1 per minute)

### For Production:
Enable Supabase email (or configure SendGrid):
1. Go to **Authentication** → **Email**
2. Follow instructions to set up email provider

## Database Setup (Optional - for future dashboard)

Create users table:

```sql
-- Enable UUID extension
CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

-- Create users table
CREATE TABLE users (
  id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
  email TEXT UNIQUE NOT NULL,
  username TEXT UNIQUE NOT NULL,
  created_at TIMESTAMP WITH TIME ZONE DEFAULT NOW(),
  updated_at TIMESTAMP WITH TIME ZONE DEFAULT NOW(),
  total_points INT DEFAULT 0,
  games_played INT DEFAULT 0,
  games_won INT DEFAULT 0,
  current_streak INT DEFAULT 0
);

-- Create Row Level Security (RLS) policies
ALTER TABLE users ENABLE ROW LEVEL SECURITY;

-- Users can read their own data
CREATE POLICY "Users can read own data"
  ON users
  FOR SELECT
  USING (auth.uid() = id);

-- Users can update their own data
CREATE POLICY "Users can update own data"
  ON users
  FOR UPDATE
  USING (auth.uid() = id);
```

## Test Authentication

### Using cURL

**Sign Up:**
```bash
curl -X POST "https://your-project.supabase.co/auth/v1/signup" \
  -H "apikey: your-anon-key" \
  -H "Content-Type: application/json" \
  -d '{
    "email": "test@example.com",
    "password": "SecurePass123!",
    "user_metadata": {"username": "testuser"}
  }'
```

**Sign In:**
```bash
curl -X POST "https://your-project.supabase.co/auth/v1/token?grant_type=password" \
  -H "apikey: your-anon-key" \
  -H "Content-Type: application/json" \
  -d '{
    "email": "test@example.com",
    "password": "SecurePass123!"
  }'
```

## Troubleshooting

### "Invalid API key" error
- Verify you copied the **anon public key** (not service_role)
- Make sure `.env` file is in correct location
- Restart application after changing `.env`

### Email not sending
- Check Authentication → Email Templates
- For local testing, use "Auto confirm email" option
- Check Supabase logs for email errors

### CORS errors
- Supabase enables CORS by default for authenticated requests
- Make sure URL in `.env` matches exactly

### Users not appearing in dashboard
- Go to **Authentication** → **Users**
- Users appear here after successful signup
- Check confirmation status (if email confirmation required)

## Security Best Practices

1. **Never commit `.env` with real credentials**
   - Add `.env` to `.gitignore`
   - Share credentials securely (not in chat/email)

2. **Rotate API keys regularly**
   - Settings → API → Rotate keys (monthly recommended)

3. **Use RLS policies**
   - Always enable Row Level Security on tables
   - Restrict data access per user

4. **Monitor authentication attempts**
   - Settings → Authentication → Rate limiting
   - Set appropriate rate limits

5. **Use strong passwords**
   - Enforce in your application (already done!)
   - Educate users on password security

## Disable New Signups (Optional)

If you want to disable public registration:
1. Go to **Authentication** → **Providers**
2. Disable **Email** provider
3. Users can only log in with pre-created accounts

To create accounts manually:
```sql
-- Use Supabase admin API (server-side only)
-- Or create through dashboard
```

## Next Steps

1. Deploy your C++ application
2. Test login/registration with real Supabase project
3. Monitor authentication attempts in Supabase dashboard
4. Set up email templates for production
5. Configure custom domain (if needed)

## Support

For Supabase issues:
- Documentation: https://supabase.com/docs
- Community: https://discord.supabase.com
- Status: https://status.supabase.com

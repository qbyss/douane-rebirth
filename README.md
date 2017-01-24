Douane-Rebirth is a fork of Douane by Guillaume Hain. It is a firewall that filter and limit the outgoing network traffic per application.

The original project can be found here : https://github.com/Douane/

You can allow network traffic for some applications and deny network traffic for other.

To sum it up, it's an outgoing firewall per application.

### The reason of this fork

I am making this fork because the official repository hasn't been updated for years and I think there is a lot of room for improvements.

Outgoing firewall is almost inexistant in the linux world but I think it's an important feature that we can find in windows, osx and android. I'm a bit paranoid, so I can't trust my binaries until I've checked the source code, and it's impossible to do it for each application.

The last reason is that I needed a reason to immerge myself in the linux kernel world. This project will help me better understand how this work.

### New features

- Restrict application not by path but by binary hash
- Recreate configuration program (no more python)
- Easy to install on Fedora (rpm)
- Notification when asking for autorisation, no more dialog popping
- Fixing init scripts for systemd
- Removing the twitter part

And probably many more.


### Licencing

The entire project is 100% open source under the GPL v2 licence.


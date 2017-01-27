Douane-Rebirth is a fork of Douane by Guillaume Hain. It is a firewall that filter and limit the outgoing network traffic per application.

The original project can be found here : https://github.com/Douane/

You can allow network traffic for some applications and deny network traffic for other.

To sum it up, it's an outgoing firewall per application.

### The reason of this fork

I am making this fork because the official repository hasn't been updated for years and I think there is a lot of room for improvements.

Outgoing firewall is almost inexistant in the linux world but I think it's an important feature that we can find in windows, osx and android. I'm a bit paranoid, so I can't trust my applications until I've checked the source code, but it's time consumming to do it for each release. So this way I can block an application I don't trust and be sure it can't access the internet.

The last reason is that I needed a reason to immerge myself in the linux kernel world. This project will help me better understand how it work.

### New features

- Restrict application not by path but by binary hash (unique id per release)
- Recreate configuration program (no more python)
- Notification when asking for autorization
- Fixing init scripts for systemd
- Advanced mode with ability to choose IPs to allow or deny for each application
- CLI

I will probably add more features as I progress in the development.


### Licencing

The entire project is 100% open source under the GPL v2 licence like the original douane.
